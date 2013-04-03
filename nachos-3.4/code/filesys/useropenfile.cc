#include "useropenfile.h"
#include <string.h>

UserOpenFile::UserOpenFile(char* fname, int idx, int id)
{
    name = new char[strlen(fname)+1];
    strcpy(name, fname);
    uid = id;
    index = idx;
    offset = 0;
}
