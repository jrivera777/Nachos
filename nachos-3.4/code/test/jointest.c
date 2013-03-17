#include "syscall.h"
int total;
void sum()
{
    int i;
    for(i = 0; i < 10; i++)
	total++;
    Exit(i); 
}

int main()
{
    int pid1 = Fork(sum);
    int pid2 = Fork(sum);

    Join(pid1); 
    Join(pid2); 
                

    total++;

    Exit(total);
}
