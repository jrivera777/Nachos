#ifndef USEROPENFILE_H
#define USEROPENFILE_H


class UserOpenFile
{
 public:
    UserOpenFile(char* fname, int idx, int id);
    ~UserOpenFile();
    int uid;
    int index;
    char* name;
    int offset;
};

#endif
