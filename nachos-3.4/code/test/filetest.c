#include "syscall.h"

int main()
{
    int dst, src1, src2;
    src1 = Open("../test/in.dat");
    if(src1 < 0)
    {
	Close(src1);
	Exit(100);
    }
    else
    {
	Close(src1);
	Exit(666);
    }
}
