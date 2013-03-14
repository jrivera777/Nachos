/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"

int total;
void printA()
{
    OpenFileId output = ConsoleOutput;
    int i;
    char test[5];
    test[0] = 'a';
    *test++;
    Write(test, 1, output);
}

int
main()
{   
    Fork(printA);
    printA();
    Halt();
    /* not reached */
}
