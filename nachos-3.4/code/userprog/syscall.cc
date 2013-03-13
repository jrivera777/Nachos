#include "syscall.h"
#include "system.h"

void Halt()
{
    DEBUG('a', "Shutdown, initiated by user program.\n");
    interrupt->Halt();
}
void ExitSC(int status)
{
    DEBUG('a', "Exit[%d], initiated by user program.\n", status);
}
SpaceId Exec(char *name)
{
    DEBUG('a', "Exec[%s], initiated by user program.\n", name);
}
int Join(SpaceId id)
{
    DEBUG('a', "Join, initiated by user program.\n");
}
void Fork(void (*func)())
{
    DEBUG('a', "Kill, initiated by user program.\n");		
}
void Yield()
{
    DEBUG('a', "Yeild, initiated by user program.\n");		
}
void Kill(SpaceId id)
{
    DEBUG('a', "Kill[%d], initiated by user program.\n", id);		
}
