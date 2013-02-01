// synch.cc 
//	Routines for synchronizing threads.  Three kinds of
//	synchronization routines are defined here: semaphores, locks 
//   	and condition variables (the implementation of the last two
//	are left to the reader).
//
// Any implementation of a synchronization routine needs some
// primitive atomic operation.  We assume Nachos is running on
// a uniprocessor, and thus atomicity can be provided by
// turning off interrupts.  While interrupts are disabled, no
// context switch can occur, and thus the current thread is guaranteed
// to hold the CPU throughout, until interrupts are reenabled.
//
// Because some of these routines might be called with interrupts
// already disabled (Semaphore::V for one), instead of turning
// on interrupts at the end of the atomic operation, we always simply
// re-set the interrupt state back to its original value (whether
// that be disabled or enabled).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synch.h"
#include "system.h"

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	Initialize a semaphore, so that it can be used for synchronization.
//
//	"debugName" is an arbitrary name, useful for debugging.
//	"initialValue" is the initial value of the semaphore.
//----------------------------------------------------------------------

Semaphore::Semaphore(char* debugName, int initialValue)
{
    name = debugName;
    value = initialValue;
    queue = new List;
}

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	De-allocate semaphore, when no longer needed.  Assume no one
//	is still waiting on the semaphore!
//----------------------------------------------------------------------

Semaphore::~Semaphore()
{
    delete queue;
}

//----------------------------------------------------------------------
// Semaphore::P
// 	Wait until semaphore value > 0, then decrement.  Checking the
//	value and decrementing must be done atomically, so we
//	need to disable interrupts before checking the value.
//
//	Note that Thread::Sleep assumes that interrupts are disabled
//	when it is called.
//----------------------------------------------------------------------

void
Semaphore::P()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    
    while (value == 0) { 			// semaphore not available
	queue->Append((void *)currentThread);	// so go to sleep
	currentThread->Sleep();
    } 
    value--; 					// semaphore available, 
						// consume its value
    
    (void) interrupt->SetLevel(oldLevel);	// re-enable interrupts
}

//----------------------------------------------------------------------
// Semaphore::V
// 	Increment semaphore value, waking up a waiter if necessary.
//	As with P(), this operation must be atomic, so we need to disable
//	interrupts.  Scheduler::ReadyToRun() assumes that threads
//	are disabled when it is called.
//----------------------------------------------------------------------

void
Semaphore::V()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    thread = (Thread *)queue->Remove();
    if (thread != NULL)	   // make thread ready, consuming the V immediately
	scheduler->ReadyToRun(thread);
    value++;
    (void) interrupt->SetLevel(oldLevel);
}

// Dummy functions -- so we can compile our later assignments 
// Note -- without a correct implementation of Condition::Wait(), 
// the test case in the network assignment won't work!
#ifdef CHANGED
Lock::Lock(void)
{
	DEBUG('t', "****Constructed Lock: %s\n", name);
}

Lock::Lock(char* debugName) 
{
	name = debugName;
	value = 1;
	queue = new List;
	heldBy = NULL;
	DEBUG('t', "****Constructed Lock: %s\n", name);
}
Lock::~Lock() 
{
	delete queue;
	heldBy = NULL;
}
void Lock::Acquire() 
{
	IntStatus oldLevel = interrupt->SetLevel(IntOff); // disable interrupts
	
	while (value == 0) 
	{ 			
		queue->Append((void *)currentThread);	
		currentThread->Sleep();
	}
	value--; 				
	heldBy = (Thread*)currentThread;
	(void) interrupt->SetLevel(oldLevel);	// re-enable interrupts
}
void Lock::Release() 
{	
	IntStatus oldLevel = interrupt->SetLevel(IntOff);
	
	if(isHeldByCurrentThread())
	{
		Thread* awake = (Thread*) queue->Remove(); //wake one thread waiting on the lock
		if(awake != NULL)
			scheduler->ReadyToRun(awake);
		value++;
		heldBy = NULL;  //current thread no longer owns lock
	}
	interrupt->SetLevel(oldLevel);
}
bool Lock::isHeldByCurrentThread()
{
	return heldBy == currentThread;
}
#else
Lock::Lock(char* debugName) {}
Lock::~Lock() {}
void Lock::Acquire() {}
void Lock::Release() {}
#endif

#ifdef CHANGED
Condition::Condition(char* debugName) 
{ 
    name = debugName;
    blocked = new List;
}
Condition::~Condition() 
{ 
    delete blocked;
}
void Condition::Wait(Lock* conditionLock) 
{
    if(conditionLock->isHeldByCurrentThread()) //Not sure if we need this check.  Synch.h description seems to suggest it.
    {
        conditionLock->Release();

	IntStatus oldLevel = interrupt->SetLevel(IntOff);
        blocked->Append((Thread*)currentThread);
        currentThread->Sleep();
	interrupt->SetLevel(oldLevel);
        conditionLock->Acquire();
    }
}
void Condition::Signal(Lock* conditionLock) 
{ 
	if(conditionLock->isHeldByCurrentThread()) //same issue as Wait()
	{
		IntStatus oldLevel = interrupt->SetLevel(IntOff);
		Thread* awake = (Thread*)blocked->Remove();
		if(awake != NULL)
			scheduler->ReadyToRun(awake);
		interrupt->SetLevel(oldLevel);
	}
}
void Condition::Broadcast(Lock* conditionLock) 
{ 
	if(conditionLock->isHeldByCurrentThread()) //same issue as Wait()
	{
		IntStatus oldLevel = interrupt->SetLevel(IntOff);
		Thread* curr;
		while((curr =(Thread*) blocked->Remove()) != NULL)
			scheduler->ReadyToRun(curr);
		interrupt->SetLevel(oldLevel);
	}
}
#else
Condition::Condition(char* debugName) { }
Condition::~Condition() { }
void Condition::Wait(Lock* conditionLock) { ASSERT(FALSE); }
void Condition::Signal(Lock* conditionLock) { }
void Condition::Broadcast(Lock* conditionLock) { }
#endif
