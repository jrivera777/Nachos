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
    AddrSpace(OpenFile *executable, int parentID);	// Create an address space,
					// initializing it with the program
					// stored in the file "executable"
    ~AddrSpace();			// De-allocate an address space

    void InitRegisters();		// Initialize user-level CPU registers,
    int Translate(int i);               // before jumping to user code

    void SaveState();			// Save/restore address space-specific
    void RestoreState();		// info on a context switch 
    AddrSpace* Fork();                  // Create duplicate address space
    int ReadFile(int virtAddr, 
		 OpenFile* file,
		 int size,
		 int fileAddr);
    PCB* pcb;
    int GetNumPages() {return numPages;};
private:
    AddrSpace();                        //constructor for Fork Operation
    void init(OpenFile* executable, int parentID);
    TranslationEntry *pageTable;	// Assume linear page table translation
					// for now!
    unsigned int numPages;		// Number of pages in the virtual 
    MemManager* manager;				// address space
};

#endif // ADDRSPACE_H
