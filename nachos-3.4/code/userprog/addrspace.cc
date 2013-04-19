// addrspace.cc 
//	Routines to manage address spaces (executing user programs).
//
//	In order to run a user program, you must:
//
//	1. link with the -N -T 0 option 
//	2. run coff2noff to convert the object file to Nachos format
//		(Nachos object code format is essentially just a simpler
//		version of the UNIX executable object code format)
//	3. load the NOFF file into the Nachos file system
//		(if you haven't implemented the file system yet, you
//		don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "pcbmanager.h"
#include "noff.h"
#include <string.h>

class PCB;

#ifdef HOST_SPARC
#include <strings.h>
#endif

//----------------------------------------------------------------------
// SwapHeader
// 	Do little endian to big endian conversion on the bytes in the 
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
	noffH->noffMagic = WordToHost(noffH->noffMagic);
	noffH->code.size = WordToHost(noffH->code.size);
	noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
	noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
	noffH->initData.size = WordToHost(noffH->initData.size);
	noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
	noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
	noffH->uninitData.size = WordToHost(noffH->uninitData.size);
	noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
	noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
// 	Create an address space to run a user program.
//	Load the program from a file "executable", and set everything
//	up so that we can start executing user instructions.
//
//	Assumes that the object code file is in NOFF format.
//
//	First, set up the translation from program memory to physical 
//	memory.  For now, this is really simple (1:1), since we are
//	only uniprogramming, and we have a single unsegmented page table
//
//	"executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------

void
AddrSpace::init(OpenFile* executable, Thread* parent, Thread *selfThread, bool replace)
{
    NoffHeader noffH;
    unsigned int i, size;
    
    executable->ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && 
		(WordToHost(noffH.noffMagic) == NOFFMAGIC))
    	SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);

    // how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
			+ UserStackSize;	// we need to increase the size
						// to leave room for the stack
    codeSize = noffH.code.size;
    initDataSize = noffH.initData.size;
    uninitDataSize = noffH.uninitData.size;

    numPages = divRoundUp(size, PageSize);
    size = numPages * PageSize;
    nextVPage = 0;
    manager = MemManager::GetInstance();

    if(replace)
	    parent->space->FreePages();
//     if(numPages > manager->GetFreePages())
//     {
// 	    printf("Not enough memory.\n");
// 	    numPages = 0;
// 	    return;
//     }

    DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
					 manager->GetFreePages(), size);

    PCBManager* pcbman = PCBManager::GetInstance();
    if(!replace){
	    pcb = new PCB(selfThread, pcbman->GetPID(), parent);
    }else{
	    pcb = parent->space->pcb;
	    delete parent->space->pageTable;
    }

    pcbman->pcbs->SortedInsert((void*)pcb, pcb->GetPID()); //keep track of new pcb
    pageTable = new TranslationEntry[numPages];

    //set up swap file name
    char swid[5];
    sprintf(swid, "%d", pcb->GetPID());
    strcat(swap,"swap.");
    strcat(swap, swid);
    fileSystem->Create(swap, 0);
    DEBUG('p', "Created swapfile = %s\n", swap);
    DEBUG('p', "Total number Pages = %d\n", numPages);
    // first, set up the translation 
    for (i = 0; i < numPages; i++) 
    {
	pageTable[i].virtualPage = i;
//	pageTable[i].physicalPage = manager->GetPage();
//	bzero(machine->mainMemory + pageTable[i].physicalPage * PageSize, PageSize);
	pageTable[i].valid = FALSE;
	pageTable[i].use = FALSE;
	pageTable[i].dirty = FALSE;
	pageTable[i].readOnly = FALSE; 
	pageTable[i].persisted = FALSE; 
    }



    //CONSERVATIVE VERSION = Write entire executable into swap file!
    OpenFile* swapFile = fileSystem->Open(swap);
    char buffer[size];
    int wrote;
    DEBUG('p', "About to read %d bytes from executable into swap\n", size);
    if(noffH.code.size > 0)
    {
	executable->ReadAt(buffer, noffH.code.size, noffH.code.inFileAddr);
    }
    if(noffH.initData.size > 0)
    {
	executable->ReadAt(buffer, noffH.initData.size, noffH.initData.inFileAddr);
    }

    DEBUG('p', "About to write %d bytes into swapfile %s\n", size, swap);
    wrote = swapFile->WriteAt(buffer, size, 0);
    DEBUG('p', "Wrote %d bytes into swapfile %s\n", wrote, swap);


    // then, copy in the code and data segments into memory
//     if (noffH.code.size > 0) 
//     {
//         DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
// 			noffH.code.virtualAddr, noffH.code.size);
// 	ReadFile(noffH.code.virtualAddr, executable, noffH.code.size,
// 		 noffH.code.inFileAddr);
//     }
//     if (noffH.initData.size > 0) 
//     {
//         DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
// 			noffH.initData.virtualAddr, noffH.initData.size);
// 	ReadFile(noffH.initData.virtualAddr, executable, noffH.initData.size,
// 			noffH.initData.inFileAddr);
// //        executable->ReadAt(&(machine->mainMemory[noffH.initData.virtualAddr]),
// //			noffH.initData.size, noffH.initData.inFileAddr);
//     }
    printf("Loaded Program: [%d] code |  [%d] data | [%d] bss\n", codeSize, 
	   initDataSize, uninitDataSize);
}

AddrSpace::AddrSpace(){}
AddrSpace::AddrSpace(OpenFile *executable)
{
  init(executable, NULL, currentThread, false);
}
AddrSpace::AddrSpace(OpenFile *executable, Thread* parent)
{
    init(executable, parent, currentThread, false);
}
AddrSpace::AddrSpace(OpenFile *executable, Thread* parent, Thread* selfThread,bool replace)
{
   init(executable, parent, selfThread, replace);
}

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
// 	Dealloate an address space.  Nothing for now!
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
   delete pageTable;
}

int 
AddrSpace::Translate(int virtAddr)
{
	int physAddr;
	int vpn = virtAddr / PageSize;
	int offset = virtAddr % PageSize;

	if(vpn >= numPages){
		DEBUG('a', "Translate VPN %d greather than %d \n",virtAddr,numPages);
		return -1;
	}
	if(! pageTable[vpn].valid){
		DEBUG('a', "Translate VPN %d Invalid \n",virtAddr);
		return -1;
	}

	physAddr = PageSize * pageTable[vpn].physicalPage + offset;
	DEBUG('a', "Translate VPN %d to PFN %d \n",virtAddr,physAddr);

	return physAddr;
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
// 	Set the initial values for the user-level register set.
//
// 	We write these directly into the "machine" registers, so
//	that we can immediately jump to user code.  Note that these
//	will be saved/restored into the currentThread->userRegisters
//	when this thread is context switched out.
//----------------------------------------------------------------------
void
AddrSpace::InitRegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);	

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!
    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to %d\n", numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
// 	On a context switch, save any machine state, specific
//	to this address space, that needs saving.
//
//----------------------------------------------------------------------

void AddrSpace::SaveState() 
{
    currentThread->SaveUserState();
}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
// 	On a context switch, restore the machine state so that
//	this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void AddrSpace::RestoreState() 
{
    machine->pageTable = pageTable;
    machine->pageTableSize = numPages;
}

AddrSpace*
AddrSpace::Fork()
{
    if(numPages > manager->GetFreePages()) {
	return NULL;
    }	
    AddrSpace* forkedSpace = new AddrSpace();
    if(forkedSpace == NULL){
	    return NULL;
    }	

    forkedSpace->numPages = numPages;
    forkedSpace->manager = manager;
    forkedSpace->codeSize = codeSize;
    forkedSpace->initDataSize = initDataSize;
    forkedSpace->uninitDataSize = uninitDataSize;
    //set up page table or copy it?
    forkedSpace->pageTable = new TranslationEntry[numPages];
    for (int i = 0; i < numPages; i++) 
    {
	forkedSpace->pageTable[i].virtualPage = i;
	forkedSpace->pageTable[i].physicalPage = manager->GetPage();
	forkedSpace->pageTable[i].valid = pageTable[i].valid;
	forkedSpace->pageTable[i].use = pageTable[i].use;
	forkedSpace->pageTable[i].dirty = pageTable[i].dirty;
	forkedSpace->pageTable[i].readOnly = pageTable[i].readOnly;
	bcopy(machine->mainMemory + pageTable[i].physicalPage * PageSize,
		machine->mainMemory + forkedSpace->pageTable[i].physicalPage * PageSize, 
		PageSize );
    }

    return forkedSpace;
}

int 
AddrSpace::ReadFile(int virtAddr, OpenFile* file, int size, int fileAddr)
{
    char buffer[size]; 
    int currentSize = file->ReadAt(buffer, size, fileAddr);
    int readSize = 0, copied=  0;
    int left = currentSize;
    int phyAddr;
    
    while (left > 0) 
    {
	phyAddr = Translate(virtAddr);
	
	ASSERT(phyAddr >= 0 );
	readSize = min(PageSize,left);
	bcopy(buffer+copied, &machine->mainMemory[phyAddr],readSize);
	
	left -= readSize;
	copied += readSize;
	virtAddr += readSize;
    }
    return currentSize;
}

void
AddrSpace::FreePages()
{
    for(int i = 0; i < numPages; i++)
	manager->ClearPage(pageTable[i].physicalPage);
}
