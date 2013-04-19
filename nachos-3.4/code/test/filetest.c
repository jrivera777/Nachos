#include "syscall.h"
int main()
{
    int dst, src1, src2;
    int read;
    char* buffer = "Hello World\n";
    Create("out.dat");
    src1 = Open("out.dat");
    if(src1 < 0)
	Exit(-1);
    else
    {
	Write(buffer, 11, src1);
	Close(src1);
	Exit(0);
    }


}
