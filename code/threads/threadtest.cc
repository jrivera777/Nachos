// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "synch.h"

// testnum is set in main.cc
int testnum = 1;
int threadsDone;
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------
#if defined(CHANGED) && defined(HW1_SEMAPHORES)
int SharedVariable; 
Semaphore *s;
void SimpleThread(int which) 
{ 
    if(s == NULL)
    {
	DEBUG('t', "USING SEMAPHORES\n");
	s = new Semaphore("shared semaphore", 1);
    }
    int num, val; 

    for(num = 0; num < 5; num++) 
    { 
	s->P();
	
	val = SharedVariable; 
	printf("*** thread %d sees value %d\n", which, val); 
	currentThread->Yield(); 
	SharedVariable = val+1; 
	
	s->V();
	
	currentThread->Yield(); 
    } 

    //We use threadsDone as a "barrier" to stop threads that finish
    // first from printing the final value.
    threadsDone--;
    while(threadsDone != 0)
	currentThread->Yield(); 
    val = SharedVariable; 
    
    printf("Thread %d sees final value %d\n", which, val);
} 
#elif defined(CHANGED) &&  defined(HW1_LOCKS)
int SharedVariable; 
Lock *testLock;
void SimpleThread(int which) 
{ 
    if(testLock == NULL)
    {
	DEBUG('t', "USING LOCKS\n");
	testLock = new  Lock("test");
    }
    int num, val; 
    
    for(num = 0; num < 5; num++) 
    { 
	testLock->Acquire();
	
	val = SharedVariable; 
	printf("*** thread %d sees value %d\n", which, val); 
	currentThread->Yield(); 
	SharedVariable = val+1; 
	
	testLock->Release();
	
	currentThread->Yield(); 
    } 
    
    //We use threadsDone as a "barrier" to stop threads that finish
    // first from printing the final value.
    threadsDone--;
    while(threadsDone != 0)
	currentThread->Yield(); 
    val = SharedVariable; 
    
    printf("Thread %d sees final value %d\n", which, val);
}
#elif defined(CHANGED) && defined(HW1_ELEVATOR)
#define MAX_CAPACITY 5

struct Floor
{
    Condition *cond;
    int numWaiting;
};

struct Floor *floors;
void Elevator(int numFloors)
{
    int i;
    floors = new struct Floor[numFloors];
    for(i = 0; i < numFloors; i++)
    {
	floors[i].cond = new Condition("floor condition");
	floors[i].numWaiting = 0;
    }
}

void ArrivingGoingFromTo(int atFloor, int toFloor)
{
}
#else
void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}
#endif

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------
#if defined(CHANGED) && defined(THREADS)
void 
ThreadTest(int n)
{
    int i;
    threadsDone = n+1;
    DEBUG('t', "threadsDone = %d\n", threadsDone);
    for(i = 0; i < n; i++)
    {
	Thread *t = new Thread("forked thread");
	t->Fork(SimpleThread, i + 1);
    }
    SimpleThread(0);
}
#endif

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, 1);
    SimpleThread(0);
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------
void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}
