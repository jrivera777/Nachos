#ifndef sysopenfile
#define sysopenfile

#include "openfile.h"
#include "list.h"

class SysOpenFile
{
	public:
		char * mFilename;
	  OpenFile * mOpenFile;
		int mCount;
		int mFileId;
		static list * gobalList; 

		SysOpenFile(char * filename, int id, OpenFile *file);
		
};
#endif
