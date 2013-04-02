#include "syscall.h"

int main()
{
    int dst, src1, src2;
    src1 = Open("../test/in.dat");
    src2 = Open("../test/in.dat");
    dst = Open("../test/nothing.dat");
    dst = Open("../test/other.dat");
    if(src1 < 0)
    {
	Close(src1);
	Close(src2);
	Close(dst);
	Exit(100);
    }
    else
    {
	Close(src1);
	Close(src2);
	Close(dst);
	Exit(666);
    }
}
