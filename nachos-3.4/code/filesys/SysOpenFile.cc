#include "SysOpenFile.h"

SysOpenFile::SysOpenFile(char * filename, int id, OpenFile *file){
	mFilename = filename;
	mFileId = id;
	mOpenFile = file;
}
