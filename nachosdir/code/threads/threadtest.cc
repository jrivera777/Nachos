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
    
    for (num = 0; num < 5; num++) 
    {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}
//****Elevator Stuff Starts Here****
#define ELEVATOR_CAPACITY 5

struct Floor
{
    int gettingOn;
    int gettingOff;
};

struct Person
{
    int id;
    int atFloor;
    int toFloor;
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
	floors[i].gettingOn = 0;
	floors[i].gettingOff = 0;
    }
    eleCond = new Condition("elevator condition");
    eleLock = new Lock("elevator lock");
    currFloor = -1;
    occupied = 0;
    direction = UP;
}

void run_elevator(int numFloors)
{
    do
    {
	//Move to next floor
	eleLock->Acquire();

	int i;
	for(i = 0; i < 50000000; i++); //elevator moving

	if(direction == UP)
       	    currFloor++;
	else if(direction == DOWN)
	    currFloor--;
	else
	    break;

	printf("Elevator arrives at floor %d.\n", currFloor + 1);

	eleLock->Release();

        //give people a chance to do stuff(when random seed is NOT used)
	currentThread->Yield(); 

	if(currFloor == numFloors - 1)
	    direction = DOWN;
	else if(currFloor == 0)
	    direction = UP;

        //Let people off elevator
	eleLock->Acquire();

	eleCond->Broadcast(eleLock);

	eleLock->Release();

	eleLock->Acquire();

	while(floors[currFloor].gettingOff > 0)
	    eleCond->Wait(eleLock);

	eleLock->Release();

	//Let people waiting on current floor get on elevator	
	eleLock->Acquire();

	eleCond->Broadcast(eleLock);
	while(floors[currFloor].gettingOn > 0 && occupied < ELEVATOR_CAPACITY)
	    eleCond->Wait(eleLock);    

	eleLock->Release();
    }
    while(1);
    printf("Elevator needs Maintenance.\n");
}

void Elevator(int numFloors)
{
    Thread* elevator = new Thread("Elevator Thread");
    init_elevator(numFloors);
    DEBUG('t', "***Set up floor data.\n");
    elevator->Fork(run_elevator, numFloors);
}

void run_person(int p)
{
    Person *person = (Person*)p;

    //Arrive at floor
    eleLock->Acquire();

    floors[person->atFloor-1].gettingOn++;
    printf("Person %d wants to go to floor %d from floor %d.\n", 
	   person->id, person->toFloor, person->atFloor);

    eleLock->Release();

    //Wait for the elevator to arrive and have space
    eleLock->Acquire();

    while(currFloor != person->atFloor-1 || occupied == ELEVATOR_CAPACITY)
	eleCond->Wait(eleLock);

    eleLock->Release();
    
    //Get on elevator and wait to arrive at desired floor
    eleLock->Acquire();

    floors[person->toFloor-1].gettingOff++;
    floors[person->atFloor-1].gettingOn--;
    occupied++;
    printf("Person %d got into the elevator at floor %d.\n", person->id, currFloor + 1);
    eleCond->Broadcast(eleLock);

    eleLock->Release();

    eleLock->Acquire();

    while(currFloor != person->toFloor-1)
	eleCond->Wait(eleLock);
   
    //Get off on desired Floor
    occupied--;
    printf("Person %d got out of the elevator at floor %d.\n", person->id, currFloor+1); 
    floors[person->toFloor-1].gettingOff--;
    eleCond->Broadcast(eleLock);

    eleLock->Release();
}
int nextID;
void ArrivingGoingFromTo(int atFloor, int toFloor)
{
    Thread* person = new Thread("Person Thread");
    Person *p = new Person;
    p->atFloor = atFloor;
    p->toFloor = toFloor;
    p->id = nextID++;
    DEBUG('t', "***Initialized person!\n");
    person->Fork(run_person,(int)p);
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
