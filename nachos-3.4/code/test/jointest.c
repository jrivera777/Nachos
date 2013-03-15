#include "syscall.h"
int total;
void sum()
{
    int i;
    for(i = 0; i < 1000; i++)
	total++;
    Exit(i);
}

int main()
{
    int pid1 = Fork(sum);
    Join(pid);

    total++;

    Exit(total);
}
