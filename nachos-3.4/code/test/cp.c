#include "syscall.h"

int main() {
	char buf[50];
        char out[50];
	SpaceId dst, src;
	int count;
        int i;

	src = Open("in.dat");
	if (src < 0) Exit(100);
        Write("cp: Input destination file name:\n", 34, ConsoleOutput );        
        i = 0;
        do{
            Read(&out[i], 1, ConsoleInput);
        } while(out[i++]!='\n');
        
        out[--i] = '\0';
        
	Create(out);
	dst = Open(out);
	if (dst < 0) Exit(-200);


	while ( (count = Read(buf, 5, src)) > 0 ) 
	{
	    Write(buf, count, dst);
	}

	Write("cp: file in.dat is copied to file ", 34, ConsoleOutput);
        Write(out, i, ConsoleOutput);
        Write("\n", 2, ConsoleOutput);
        Close(src);
        Close(dst);
	Exit(0);
}
