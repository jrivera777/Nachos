// addrspace.h 
//	Data structures to keep track of executing user programs 
//	(address spaces).
//
//	For now, we don't keep any information about address spaces.
//	The user level CPU state is saved and restored in the thread
//	executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

class MemManager;
class PCB;

#include "copyright.h"
#include "filesys.h"
#include "memmanager.h"
#include "pcb.h"
#define UserStackSize		1024 	// increase this as necessary!

class AddrSpace {
  public:
    AddrSpace(OpenFile *executable);
    AddrSpace(OpenFile *executable, Thread* parent);	// Create an address space,
    AddrSpace(OpenFile *executable, Thread* parent, Thread* selfThread, bool replace);	// Create an address space,
    ~AddrSpace();					// initializing it with the program
                                                        // stored in the file "executable"
    			
    int GetNumPages() {return numPages;};
    void InitRegisters();		// Initialize user-level CPU registers,
    int Translate(int i);               // before jumping to user code

    void SaveState();			// Save/restore address space-specific
    void RestoreState();		// info on a context switch 
    AddrSpace* Fork();                  // Create duplicate address space
    void FreePages();                   //Free allocated physical pages
    int ReadFile(int virtAddr, 
		 OpenFile* file,
		 int size,
		 int fileAddr);
    PCB* pcb;
    char swap[10];
    int codeSize;
    int initDataSize;
    int uninitDataSize;
    int nextVPage;
    TranslationEntry *pageTable;
private:
    AddrSpace();   //empty constructor for Fork Operation
    void init(OpenFile* executable, Thread* parent, Thread* selfThread, bool replace); //moved noff data reading and page table building here
    unsigned int numPages;		                 
    MemManager* manager;  //Memory Manager reference
};

#endif // ADDRSPACE_H
