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
void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}
//****Elevator Stuff Starts Here****
#define ELEVATOR_CAPACITY 5

struct Floor
{
    Condition *fCond;
    Lock* fLock;
    int gettingOn;
    int gettingOff;
};

enum Direction {UP, DOWN, NONE};

struct Floor *floors;
Condition* eleCond;
Lock* eleLock;
Direction direction = UP;
int currFloor;
int occupied;
void init_elevator(int numFloors)
{
    int i;
    floors = new struct Floor[numFloors];
    for(i = 0; i < numFloors; i++)
    {
	floors[i].fCond = new Condition("floor condition");
	floors[i].fLock = new Lock("floor lock");
	floors[i].gettingOn = 0;
	floors[i].gettingOff = 0;
    }
    eleCond = new Condition("elevator condition");
    eleLock = new Lock("elevator lock");
    currFloor = 0;
    occupied = 0;
    direction = UP;
}

void run_elevator(int numFloors)
{
    while(1)
    {
	if(direction == NONE)
	    break;

	int i;
	for(i = 0; i < 50; i++); //elevator moving
	printf("Elevator arrives at floor %d.\n", currFloor + 1);

	if(currFloor == numFloors - 1)
	    direction = DOWN;
	else if(currFloor == 0)
	    direction = UP;

	//Attempt to let people off elevator
	eleLock->Acquire();
	eleCond->Broadcast(eleLock);
	eleLock->Release();

	if(direction == UP)
	{
	    currFloor++;
	}
	else if(direction == DOWN)
	{
	    currFloor--;
	}
	else
	    break;
    }
    printf("Elevator needs Maintenance.\n");
}

void Elevator(int numFloors)
{
    Thread* elevator = new Thread("Elevator Thread");
    init_elevator(numFloors);
    printf("***Set up floor data.\n");
    elevator->Fork(run_elevator, numFloors);
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

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------
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
