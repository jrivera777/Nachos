#include "syscall.h"

int gbl_pid = 0;


void suicide()
{
    Kill(gbl_pid);
   

    Exit(0);
}

void test()
{
    int i;
    for(i = 0; i < 10; i++);
    
    Yield();

    for(;i < 20; i++);

    Exit(i);
}

int main()
{
    int check = 0;
    int pid2;
    switch (check)
    {
	case 0: // test murder
	{
	    int pid = Fork(test);
	    
	    Yield();
	    
	    if(!Kill(pid))
	    {
		pid = Fork(test);
		pid2 = Fork(test);
		Join(pid2);
		Exit(pid2);
	    }
	    else
		Exit(1);
	}
	case 1: //test suicide
	{
	    gbl_pid = Fork(suicide);
	    Yield();
	    Exit(gbl_pid);
	}
	default: //test bad kill
	    Kill(666);
    }
    Exit(0);
}
