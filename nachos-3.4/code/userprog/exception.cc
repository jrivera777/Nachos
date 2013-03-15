// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "pcbmanager.h"
#include "pcb.h"

//Move PC register to next instruction
//Update PrevPC and NextPC registers appropriately
void
UpdatePCRegs()
{
    int pc = machine->ReadRegister(PCReg);

    machine->WriteRegister(PrevPCReg, pc);
    machine->WriteRegister(PCReg, pc + 4);
    machine->WriteRegister(NextPCReg, pc + 8);  
}

void
DummyFunction(int pc)
{
    DEBUG('a', "Entered dummy function with PC=[%d]\n", pc);
    currentThread->RestoreUserState();  
    machine->Run();
}

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
    if(which == SyscallException)
    {
	switch(type)
	{
	    case SC_Halt:
	    {
		DEBUG('a', "Shutdown, initiated by user program.\n");
		printf("System Call: [%d] invoked Halt\n", currentThread->space->pcb->GetPID() + 1);
		interrupt->Halt();

		break;
	    }
	    case SC_Exit:
	    {
		int status = machine->ReadRegister(4); // retreive given exit status

		DEBUG('a', "Exit[%d], initiated by user program.\n", status);

		printf("System Call: [%d] invoked Exit\n", currentThread->space->pcb->GetPID());

		PCB* currentPCB = currentThread->space->pcb;
		if(!currentPCB->children->IsEmpty()) //If process has children, they must become zombies
		    currentPCB->OrphanChildren();

		DEBUG('a', "Orphaned children\n");

		Thread* parent = currentPCB->GetParent();
		if(parent != NULL) //If process has parent,it  must be removed from the parent's list of children
		{
		    DEBUG('a', "Attempt to remove self[%d]\n", currentPCB->GetPID());

		    parent->space->pcb->RemoveChild(currentPCB->GetPID());

		    DEBUG('a', "Removed self from parent\n");

		    currentPCB->SetExitStatus(currentPCB->GetParent()->space->pcb->GetPID());  //exit status is parent's pid
		    DEBUG('a', "Set exit status\n");
		}
		

		PCBManager* manager = PCBManager::GetInstance();
		manager->RemovePCB(currentPCB->GetPID()); //remove PCB from list of PCBs
		manager->ClearPID(currentPCB->GetPID()); //free up pid

		currentThread->space->FreePages(); // free up pages

		Lock* pcbLock = currentPCB->pcbLock;
		pcbLock->Acquire();
		currentPCB->pcbCond->Broadcast(pcbLock); //wake up any threads waiting for finish
		pcbLock->Release();

		printf("Process [%d] exited with status [%d]\n", currentPCB->GetPID(), status);
		currentThread->Finish();
		break;
	    }	    
	    case SC_Exec:
	    {
		char* path = (char*)machine->ReadRegister(4); //get executable path
		int pid = -1;
		
		DEBUG('a', "Exec[%s], initiated by user program.\n", path);
		printf("System Call: [%d] invoked Exec\n", currentThread->space->pcb->GetPID() + 1);
		
		if(pid >= 0)
		    machine->WriteRegister(2, 1);
		    
		break;
	    }
	    case SC_Join:
	    {
		int pid = machine->ReadRegister(4); //get process to join
		int status = -1;

		DEBUG('a', "Join[%d], initiated by user program.\n", pid);

		printf("System Call: [%d] invoked Join\n", currentThread->space->pcb->GetPID());

		PCB* child = (PCB*)currentThread->space->pcb->GetChild(pid);
		Lock* pcbLock = child->pcbLock;
		if(child != NULL)
		{
		    pcbLock->Acquire();
		    child->pcbCond->Wait(pcbLock); //wait for child process to finish
		    pcbLock->Release();

		    status = child->GetExitStatus();
		} 

		machine->WriteRegister(2, status);

		break;
	    }
	    case SC_Fork:
	    {
		DEBUG('a', "Fork, initiated by user program.\n");

		printf("System Call: [%d] invoked Fork\n", currentThread->space->pcb->GetPID());

		currentThread->space->SaveState(); //save old registers

		PCBManager* manager = PCBManager::GetInstance();
		AddrSpace* fSpace = currentThread->space->Fork(); //make duplicate address space

		Thread* fThread = new Thread("forked thread");

		int pc =  machine->ReadRegister(4);		
		//copy old register values into new thread;
		for(int i = 0; i < NumTotalRegs; i++)
		{
		    fThread->SetUserRegister(i, currentThread->GetUserRegister(i));
		}
		fThread->SetUserRegister(PCReg, pc); //set PC to whatever is in r4
		fThread->SetUserRegister(NextPCReg, pc+4);

		int pid = manager->GetPID(); //find next available pid
		ASSERT(pid >= 0);
		PCB* pcb = new PCB(fThread, pid, currentThread);
	       
		//add new thread pcb to children of current thread
		currentThread->space->pcb->children->SortedInsert((void*)pcb, pcb->GetPID());

		fSpace->pcb = pcb;
		manager->pcbs->SortedInsert((void*)pcb, pcb->GetPID()); //insert into list of pcbs, sorted by pid

		printf("Process [%d] Fork: start at address [0x%x] with [%d] pages memory\n", 
			       currentThread->space->pcb->GetPID(), pc, fSpace->GetNumPages());
		fThread->space = fSpace;

		fThread->Fork(DummyFunction, pc);
		
		machine->WriteRegister(2, pid);
		break;
	    }
	    case SC_Kill:
	    {		
		int pid = machine->ReadRegister(2); //get process to kill

		DEBUG('a', "Kill[%d], initiated by user program.\n", pid);
		printf("System Call: [%d] invoked Kill\n", currentThread->space->pcb->GetPID());
		break;
	    }
	    case SC_Yield:
	    {
		DEBUG('a', "Yeild, initiated by user program %s.\n", currentThread->getName());
		
		if(currentThread->space->pcb->GetParent())
		    DEBUG('a', "CurrentThread pcb = {%d,%d}\n", currentThread->space->pcb->GetPID(), 
			  currentThread->space->pcb->GetParent()->space->pcb->GetPID());
		else
		    DEBUG('a', "CurrentThread pcb = {%d,%d}\n", currentThread->space->pcb->GetPID(), "NULL");

		printf("System Call: [%d] invoked Yield\n", currentThread->space->pcb->GetPID());		

//		currentThread->space->SaveState();
		currentThread->Yield();
//		currentThread->RestoreUserState();
		
		break;
	    }
	}
    }
    else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
    UpdatePCRegs();
}

