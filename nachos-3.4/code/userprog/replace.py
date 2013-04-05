import sys
import os

f = open("Makefile")
s = ""
#remove script name from args 
sys.argv.pop(0)
#edit make file and put it in a buffer
for line in f:
    if line[0:9] == "DEFINES =":
        s += "DEFINES = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS_STUB"
        for i in sys.argv:
            s+= " " + i
        s += "\n"
	#comment out the line below if not on nachos.cs.fiu.edu
        s += "INCPATH = -I../bin -I../filesys -I../userprog -I../threads -I../machine\n"
    else:
        s += line

f.close()
#put buffer in makefile
f = open("Makefile", "w")
f.write(s)
f.close()
os.system("touch *.cc *.h")
os.system("make")
