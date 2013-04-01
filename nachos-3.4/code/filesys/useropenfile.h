#ifndef USEROPENFILE_H
#define USEROPENFILE_H


class UserOpenFile
{
 public:
    UserOpenFile(char* fname, int idx);
    ~UserOpenFile();
    int index;
    char* name;
    int offset;
};

#endif
