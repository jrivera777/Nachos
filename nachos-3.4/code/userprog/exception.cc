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
DummyFunction(int i)
{
    currentThread->space->RestoreState();    
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

		interrupt->Halt();

		break;
	    }
	    case SC_Exit:
	    {
		int status = machine->ReadRegister(4);

		DEBUG('a', "Exit[%d], initiated by user program.\n", status);

		break;
	    }	    
	    case SC_Exec:
	    {
		char* path = (char*)machine->ReadRegister(4); //get executable path
		int pid = -1;
		
		DEBUG('a', "Exec[%s], initiated by user program.\n", path);
		
		if(pid >= 0)
		    machine->WriteRegister(2, 1);
		    
		break;
	    }
	    case SC_Join:
	    {
		int pid = machine->ReadRegister(4); //get process to join
		int status = -1;

		DEBUG('a', "Join[%d], initiated by user program.\n", pid);

		machine->WriteRegister(2, status);

		break;
	    }
	    case SC_Fork:
	    {
		DEBUG('a', "Fork, initiated by user program.\n");
		printf("%s\n", currentThread->getName());
		if(!currentThread->space->pcb)
		    printf("NO SPACE\n");
		printf("System Call: %d invoked Fork\n", currentThread->space->pcb->GetPID());
		currentThread->space->SaveState(); //save old registers
		DEBUG('a', "Saved address space.\n");
		PCBManager* manager = PCBManager::GetInstance();
		DEBUG('a', "About to fork duplicate address space\n");
		AddrSpace* fSpace = currentThread->space->Fork(); //make duplicate address space

		DEBUG('a', "Duplicated Address space %d.\n", fSpace->GetNumPages());
		Thread* fThread = new Thread("forked thread");
		DEBUG('a', "Created new Thread.\n");
		
		//copy old register values into new thread;
		fThread->SaveUserState();
		DEBUG('a', "Copied registers into new thread.\n");
		
		int pc =  machine->ReadRegister(4);
		fThread->setUserRegister(PCReg, pc); //set PC to whatever is in r4
		int pid = manager->GetPID(); //find next available pid
		DEBUG('a', "New thread got pid=%d.\n", pid);
		ASSERT(pid >= 0);

		PCB* pcb = new PCB(fThread, pid, 
				   currentThread->space->pcb->GetPID());
		DEBUG('a', "New thread PCB = {%s,%d,%d}.\n", currentThread->getName(), pcb->GetPID(), pcb->GetParentPID());
		//fSpace->pcb = pcb;

		manager->pcbs->Append((void*)pcb);

		printf("Process [%d] Fork: start at address [%x] with [%d] pages memory\n", 
			       pid, pc, fSpace->GetNumPages());
		DEBUG('a', "New thread PCB = {%s,%d,%d}.\n", currentThread->getName(), pcb->GetPID(), pcb->GetParentPID());
		fThread->space = fSpace;
		//fThread->Fork(DummyFunction, pid);
		//currentThread->space->RestoreState();
		
		machine->WriteRegister(2, pid);
		break;
	    }
	    case SC_Kill:
	    {		
		int pid = machine->ReadRegister(2); //get process to kill

		DEBUG('a', "Kill[%d], initiated by user program.\n", pid);

		break;
	    }
	    case SC_Yield:
	    {
		DEBUG('a', "Yeild, initiated by user program.\n");
		
		currentThread->Yield();

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

