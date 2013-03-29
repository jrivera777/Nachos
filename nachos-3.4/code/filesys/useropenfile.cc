#include "useropenfile.h"

UserOpenFile::UserOpenFile(char* fname, int id)
{
    name = fname;
    index = id;
    offset = 0;
}
