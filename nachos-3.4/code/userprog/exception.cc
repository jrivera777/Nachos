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

#include <stdio.h>
#include <string.h>
#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "pcbmanager.h"
#include "pcb.h"
#include "filesys.h"
#include "filemanager.h"
#include "addrspace.h"



int UserRead(int virtAddr, char * buffer, int size)
{
	int pos = 0,copied =0, left = 0, copy_size;
	int phyAddr;

	while ( size > 0 ) 
	{
	    machine->Translate(virtAddr, &phyAddr, 1,FALSE);
	    left = PageSize - (phyAddr) % PageSize;
	    copy_size = min( left, size);
	    bcopy ( buffer + copied,&machine->mainMemory[phyAddr], copy_size);
	    size -= copy_size;
	    copied += copy_size;
	    virtAddr += copy_size;
	}	
	return copied;
}

int UserWrite(int virtAddr, char * buffer, int size)
{
	int pos = 0,copied =0, left = 0, copy_size;
	int phyAddr;

	while ( size > 0 ) 
	{
	    machine->Translate(virtAddr, &phyAddr, 1,FALSE);
	    left = PageSize - (phyAddr) % PageSize;
	    copy_size = min( left, size);
	    bcopy (&machine->mainMemory[phyAddr], buffer + copied, copy_size);
	    size -= copy_size;
	    copied += copy_size;
	    virtAddr += copy_size;
	}	
	return copied;
}
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
    currentThread->space->RestoreState();	
    machine->Run();
}

void
readPath(char *path, int cmd)
{
	int pos = 0,copied =0;
	int phyAddr;

	do {
		machine->Translate(cmd, &phyAddr, 1,FALSE);
		bcopy(&machine->mainMemory[phyAddr], path + copied, 1);
		copied++;
		cmd++;
	}while(path[pos++] != 0);
	path[pos]='\0';
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

    if(which == PageFaultException)
    {
	int badVAddr = machine->ReadRegister(BadVAddrReg);
	DEBUG('p', "Page Fault occurred at VA=0x%x\n", badVAddr);
    }
    if(which == SyscallException)
    {
	switch(type)
	{
	    case SC_Halt:
	    {
		DEBUG('a', "Shutdown, initiated by user program.\n");
		printf("System Call: [%d] invoked Halt\n", currentThread->space->pcb->GetPID());
		interrupt->Halt();

		break;
	    }
	    case SC_Create:
	    {
		char path[32];

		printf("System Call: [%d] invoked Create\n", currentThread->space->pcb->GetPID());

                readPath(path,machine->ReadRegister(4)); //get executable path
		fileSystem->Create(path, 0);

		break;
	    }
	    case SC_Open:
	    {
		char path[32];
		int newFileID = -1;
		printf("System Call: [%d] invoked Open\n", currentThread->space->pcb->GetPID());

                readPath(path,machine->ReadRegister(4)); //get executable path
		DEBUG('w', "Read File name \"%s\"\n", path);
		int sysfid = fileManager->GetSysOpenFile(path);

		if(sysfid < 0)
		{
		    DEBUG('w', "File \"%s\" not in File Table!\n", path);
		    OpenFile* ofile = fileSystem->Open(path);
		    if(ofile == NULL)
			printf("File \"%s\" not found!\n", path);
		    else
		    {
			int id = fileManager->GetFID();
			if(id < 0)
			    printf("Failed to Open file \"%s\". No more system files allowed!\n", path);
			else
			{
			    PCB* currPCB = currentThread->space->pcb;
			    DEBUG('w', "File \"%s\" now has sysfid %d\n", path, id);
			    SysOpenFile* sfile = new SysOpenFile(id, path, ofile);
			    sfile->count++;
			    fileManager->files[id] = sfile;

			    int uid = currPCB->GetUID();
			    if(uid < 0)
				printf("Failed to Open file \"%s\". No more user files allowed!\n", path);
			    else
			    {
				UserOpenFile* ufile = new UserOpenFile(path, id, uid);
				DEBUG('w', "File starting offset is %d\n", ufile->offset);
				DEBUG('w', "File \"%s\" now has uid %d\n", path, uid);
				currPCB->files->SortedInsert((void*)ufile, uid);
				newFileID = uid;
			    }
			}
		    }
		}
		else
		{
		    PCB* currPCB = currentThread->space->pcb;
		    int uid = currPCB->GetUID();
		    if(uid < 0)
			printf("Failed to Open file \"%s\". No more user files allowed!\n", path);
		    else
		    {
			DEBUG('w', "\"%s\" already exists with id %d.\n", path, sysfid);
			fileManager->files[sysfid]->count++;
			DEBUG('w', "System file \"%s\" now has %d process(es) using it.\n", path, fileManager->files[sysfid]->count);		    
			
			UserOpenFile* ufile = new UserOpenFile(path, sysfid, uid);
			DEBUG('w', "File starting offset is %d\n", ufile->offset);
			currPCB->files->SortedInsert((void*)ufile, uid);
			DEBUG('w', "File \"%s\" now has uid %d\n", path, uid);
			newFileID = uid;
		    }
		}

		machine->WriteRegister(2, newFileID);
		break;
	    }
	    case SC_Close:
	    {
		printf("System Call: [%d] invoked Close\n", currentThread->space->pcb->GetPID());

		int uid = machine->ReadRegister(4);
		if(uid >= 2)
		{
		    PCB* currPCB = currentThread->space->pcb;
		    UserOpenFile* ufile = (UserOpenFile*)currPCB->files->Remove(uid);
		    if(ufile != NULL)
		    {
			DEBUG('w', "Found UserOpenFile to remove with uid = %d\n", uid);
			fileManager->files[ufile->index]->count--;
			if(fileManager->files[ufile->index]->count > 0)
			    DEBUG('w', "%d process(es) now watching file %d\n", fileManager->files[ufile->index]->count, ufile->index);
			else
			{
			    DEBUG('w', "No more references to file %d\n", uid);
			    fileManager->files[ufile->index] = NULL;
			    fileManager->ClearFID(ufile->index);
			}
		    }
		}
		break;
	    }
	    case SC_Write:
	    {
		printf("System Call: [%d] invoked Write\n", currentThread->space->pcb->GetPID());
		int buffer_pointer,size, file_id ;
		char *buffer;
		int size_writed;
		OpenFile* file;
		
		buffer_pointer = machine->ReadRegister(4);
		size = machine->ReadRegister(5);
		file_id = machine->ReadRegister(6);
		
		if (file_id == ConsoleOutput) 
		{
		    buffer = new char[size +1];
		    UserWrite(buffer_pointer, buffer, size);
		    buffer[size] ='\0';
		    printf("%s",buffer);
		}
		else if(file_id != ConsoleInput)
		{
		    buffer = new char[size];
		    size_writed = UserWrite(buffer_pointer, buffer, size);
		    
		    UserOpenFile * uof = (UserOpenFile *) currentThread->space->pcb->files->GetElement(file_id);
		    if(uof != NULL)
		    {
			file = fileManager->files[uof->index]->file;
			file->WriteAt(buffer, size,  uof->offset);
			uof->offset += size_writed;
		    }
		}
		break;
	    }
	    case SC_Read:
            {
		printf("System Call: [%d] invoked Read\n", currentThread->space->pcb->GetPID());
		int size;
		int buffer;
		int id, i, read;
		OpenFile* f;

		buffer = machine->ReadRegister(4);
		size = machine->ReadRegister(5);
		id = machine->ReadRegister(6);
		read = -1;

		char result[size+1];
		if(id != ConsoleOutput)
		{
		    if(id == ConsoleInput)
		    {
			for(i = 0; i < size; i++)
			{
			    result[i] = getchar();
			    read = i;
			}
			result[size] = '\0';
		    }
		    else
		    {
			UserOpenFile * uof = (UserOpenFile *) currentThread->space->pcb->files->GetElement(id);
			if(uof !=NULL)
			{
			    DEBUG('w', "About to read %d bytes, starting at offset %d, from file %d\n", size, uof->offset, id);
			    f = fileManager->files[uof->index]->file;
			    fileManager->fidLock->Acquire();
			    read = f->ReadAt(result, size, uof->offset);
			    fileManager->fidLock->Release();
			    uof->offset += read;
			    result[size] = '\0';
			}
		    }
		    
		    int bR = UserRead(buffer, result, size);
		    DEBUG('w', "Bytes Read: %d\n", bR);
		}
		machine->WriteRegister(2, read);
		
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
		//PCBManager* manager = PCBManager::GetInstance();
		char path[32];
		int pid = -1;

                readPath(path,machine->ReadRegister(4)); //get executable path
		
		DEBUG('a', "Exec[%s], initiated by user program.\n",path);
		printf("System Call: [%d] invoked Exec\n", currentThread->space->pcb->GetPID());
	
		OpenFile *executable = fileSystem->Open(path);
		if (executable == NULL) {
			printf("Unable to open file %s\n", path);
			machine->WriteRegister(2, -1);
			break;
		}

		AddrSpace* eSpace = new AddrSpace(executable, currentThread, currentThread, true);
		if(eSpace == NULL){
			printf("Unable to create Address Space\n");
			machine->WriteRegister(2, -1);
			break;
		}

		pid = eSpace->pcb->GetPID();
		DEBUG('a', "Exec[%s], address space created pid[%d].\n",path,pid);
		printf("Exec Program: [%d] loading [%s]\n", pid, path);
		delete executable; 
		if(pid >= 0)
		    machine->WriteRegister(2, pid);
		else
			machine->WriteRegister(2, -1);

		eSpace->InitRegisters();
		currentThread->space = eSpace;
		eSpace->RestoreState();
		machine->Run();

		break;
	    }
	    case SC_Join:
	    {
		int pid = machine->ReadRegister(4); //get process to join
		int status = -1;

		DEBUG('a', "Join[%d], initiated by user program.\n", pid);

		printf("System Call: [%d] invoked Join\n", currentThread->space->pcb->GetPID());

		PCB* child = (PCB*)currentThread->space->pcb->GetChild(pid);

		if(child != NULL)
		{
		    Lock* pcbLock = child->pcbLock;
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
		PCBManager* manager = PCBManager::GetInstance();
		DEBUG('a', "Fork, initiated by user program.\n");

		printf("System Call: [%d] invoked Fork\n", currentThread->space->pcb->GetPID());

		currentThread->space->SaveState(); //save old registers

		AddrSpace* fSpace = currentThread->space->Fork(); //make duplicate address space
		if(fSpace == NULL){
			printf("Unable to create Address Space\n");
			machine->WriteRegister(2, -1);
			break;
		}

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
		int pid = machine->ReadRegister(4); //get process to kill
		int succ = -1;
		PCB* assassin = currentThread->space->pcb;
		PCBManager* manager = PCBManager::GetInstance();

		printf("System Call: [%d] invoked Kill\n", assassin->GetPID());
		
		if(manager->pcbs->Contains(pid))
		{

		    if(pid == assassin->GetPID())
		    {
			DEBUG('a', "Proces [%d] committing seppuku...\n", pid);
			machine->WriteRegister(2, SC_Exit);
			ExceptionHandler(which);
		    }
		    else
		    {
			PCB* victim = (PCB*)manager->pcbs->GetElement(pid);
			if(!victim->children->IsEmpty())  //process to be killed has children
			    victim->OrphanChildren();

			Thread* parent = victim->GetParent();
			if(parent != NULL) //If process has parent,it  must be removed from the parent's list of children
			{
			    DEBUG('a', "Attempt to remove self[%d]\n", pid);

			    parent->space->pcb->RemoveChild(pid);
			    
			    DEBUG('a', "Removed self from parent\n");
			    
			    victim->SetExitStatus(assassin->GetPID());  //exit status is parent's pid
			}
			manager->RemovePCB(pid); // remove killed process from list of all processes
			manager->ClearPID(pid); // free pid used by killed process
			victim->GetThread()->space->FreePages(); //free memory used by killed process
			threadToBeDestroyed = victim->GetThread();
			
			Lock* pcbLock = victim->pcbLock;
			pcbLock->Acquire();
			victim->pcbCond->Broadcast(pcbLock); //wake up any threads waiting for finish
			pcbLock->Release();			
			
			scheduler->FindNextToRun();

			succ = 0;
			printf("Process [%d] killed process [%d]\n", assassin->GetPID(), pid);
		    }
		}
		else
		    printf("Process [%d] cannot kill process [%d]:doesn't exist\n", 
			   currentThread->space->pcb->GetPID(), pid);

		machine->WriteRegister(2, succ);
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

