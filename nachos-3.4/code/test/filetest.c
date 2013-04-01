#include "syscall.h"

int main()
{
    int dst, src1, src2;
    src1 = Open("in.dat");
    src2 = Open("in.dat");
    dst = Open("womp.dat");
    if(src1 < 0)
    {
	Close(src1);
	Close(src2);
	Exit(100);
    }
    else
    {
	Close(src1);
	Close(src2);
	Exit(666);
    }
}
