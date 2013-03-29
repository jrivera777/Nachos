#include "sysopenfile.h"

SysOpenFile::SysOpenFile(int id, char* fname, OpenFile* f){
	name = fname;
	file = f;
	fid = id;
}
