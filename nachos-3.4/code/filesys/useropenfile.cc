#include "useropenfile.h"

UserOpenFile::UserOpenFile(char* fname, int idx)
{
    name = fname;
    index = idx;
    offset = 0;
}
