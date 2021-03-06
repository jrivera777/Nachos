# NOTE: this is a GNU Makefile.  You must use "gmake" rather than "make".
#
# Makefile for the virtual memory assignment
#    Defines set up assuming the virtual memory assignment is done before 
# 	the file system assignment. If not, use the "filesys first"  
#	defines below. 
#
# Also, if you want to simplify the translation so it assumes
# only linear page tables, don't define USE_TLB.
#
# Copyright (c) 1992 The Regents of the University of California.
# All rights reserved.  See copyright.h for copyright notice and limitation 
# of liability and disclaimer of warranty provisions.

DEFINES = -DUSER_PROGRAM  -DFILESYS_NEEDED -DFILESYS_STUB -DVM -DUSE_TLB
INCPATH = -I../filesys -I../bin -I../vm -I../userprog -I../threads -I../machine
HFILES = $(THREAD_H) $(USERPROG_H) $(VM_H)
CFILES = $(THREAD_C) $(USERPROG_C) $(VM_C)
C_OFILES = $(THREAD_O) $(USERPROG_O) $(VM_O)

# if file sys done first!
# DEFINES = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS -DVM -DUSE_TLB
# INCPATH = -I../vm -I../bin -I../filesys -I../userprog -I../threads -I../machine
# HFILES = $(THREAD_H) $(USERPROG_H) $(FILESYS_H) $(VM_H)
# CFILES = $(THREAD_C) $(USERPROG_C) $(FILESYS_C) $(VM_C)
# C_OFILES = $(THREAD_O) $(USERPROG_O) $(FILESYS_O) $(VM_O)

include ../Makefile.common
include ../Makefile.dep
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
main.o: ../threads/main.cc ../threads/copyright.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/system.h ../threads/thread.h \
  ../machine/machine.h ../threads/utility.h ../machine/translate.h \
  ../machine/disk.h ../userprog/addrspace.h ../threads/copyright.h \
  ../filesys/filesys.h ../threads/copyright.h ../filesys/openfile.h \
  ../threads/utility.h ../userprog/memmanager.h ../threads/synch.h \
  ../threads/list.h ../userprog/bitmap.h ../threads/utility.h \
  ../filesys/openfile.h ../userprog/addrspace.h ../userprog/pcb.h \
  ../threads/thread.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h ../threads/scheduler.h ../machine/interrupt.h \
  ../threads/list.h ../machine/stats.h ../machine/timer.h \
  ../filesys/filesys.h ../filesys/filemanager.h
list.o: ../threads/list.cc ../threads/copyright.h ../threads/list.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h
scheduler.o: ../threads/scheduler.cc ../threads/copyright.h \
  ../threads/scheduler.h ../threads/list.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/thread.h ../machine/machine.h \
  ../threads/utility.h ../machine/translate.h ../machine/disk.h \
  ../userprog/addrspace.h ../threads/copyright.h ../filesys/filesys.h \
  ../threads/copyright.h ../filesys/openfile.h ../threads/utility.h \
  ../userprog/memmanager.h ../threads/synch.h ../userprog/bitmap.h \
  ../threads/utility.h ../filesys/openfile.h ../userprog/addrspace.h \
  ../userprog/pcb.h ../threads/thread.h ../threads/list.h \
  ../filesys/filemanager.h ../userprog/bitmap.h ../threads/synch.h \
  ../filesys/sysopenfile.h ../filesys/useropenfile.h ../threads/system.h \
  ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
  ../machine/timer.h ../filesys/filesys.h ../filesys/filemanager.h
synch.o: ../threads/synch.cc ../threads/copyright.h ../threads/synch.h \
  ../threads/thread.h ../threads/utility.h ../threads/bool.h \
  ../machine/sysdep.h ../threads/copyright.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/machine.h ../threads/utility.h \
  ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
  ../threads/copyright.h ../filesys/filesys.h ../threads/copyright.h \
  ../filesys/openfile.h ../threads/utility.h ../userprog/memmanager.h \
  ../threads/synch.h ../userprog/bitmap.h ../threads/utility.h \
  ../filesys/openfile.h ../userprog/addrspace.h ../userprog/pcb.h \
  ../threads/thread.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h ../threads/list.h ../threads/system.h \
  ../threads/scheduler.h ../machine/interrupt.h ../threads/list.h \
  ../machine/stats.h ../machine/timer.h ../filesys/filesys.h \
  ../filesys/filemanager.h
synchlist.o: ../threads/synchlist.cc ../threads/copyright.h \
  ../threads/synchlist.h ../threads/list.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/synch.h ../threads/thread.h \
  ../machine/machine.h ../threads/utility.h ../machine/translate.h \
  ../machine/disk.h ../userprog/addrspace.h ../threads/copyright.h \
  ../filesys/filesys.h ../threads/copyright.h ../filesys/openfile.h \
  ../threads/utility.h ../userprog/memmanager.h ../threads/synch.h \
  ../userprog/bitmap.h ../threads/utility.h ../filesys/openfile.h \
  ../userprog/addrspace.h ../userprog/pcb.h ../threads/thread.h \
  ../threads/list.h ../filesys/filemanager.h ../userprog/bitmap.h \
  ../threads/synch.h ../filesys/sysopenfile.h ../filesys/useropenfile.h
system.o: ../threads/system.cc ../threads/copyright.h ../threads/system.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/thread.h ../machine/machine.h \
  ../threads/utility.h ../machine/translate.h ../machine/disk.h \
  ../userprog/addrspace.h ../threads/copyright.h ../filesys/filesys.h \
  ../threads/copyright.h ../filesys/openfile.h ../threads/utility.h \
  ../userprog/memmanager.h ../threads/synch.h ../threads/list.h \
  ../userprog/bitmap.h ../threads/utility.h ../filesys/openfile.h \
  ../userprog/addrspace.h ../userprog/pcb.h ../threads/thread.h \
  ../threads/list.h ../filesys/filemanager.h ../userprog/bitmap.h \
  ../threads/synch.h ../filesys/sysopenfile.h ../filesys/useropenfile.h \
  ../threads/scheduler.h ../machine/interrupt.h ../threads/list.h \
  ../machine/stats.h ../machine/timer.h ../filesys/filesys.h \
  ../filesys/filemanager.h
thread.o: ../threads/thread.cc ../threads/copyright.h ../threads/thread.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/machine.h ../threads/utility.h \
  ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
  ../threads/copyright.h ../filesys/filesys.h ../threads/copyright.h \
  ../filesys/openfile.h ../threads/utility.h ../userprog/memmanager.h \
  ../threads/synch.h ../threads/list.h ../userprog/bitmap.h \
  ../threads/utility.h ../filesys/openfile.h ../userprog/addrspace.h \
  ../userprog/pcb.h ../threads/thread.h ../threads/list.h \
  ../filesys/filemanager.h ../userprog/bitmap.h ../threads/synch.h \
  ../filesys/sysopenfile.h ../filesys/useropenfile.h ../threads/switch.h \
  ../threads/synch.h ../threads/system.h ../threads/scheduler.h \
  ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
  ../machine/timer.h ../filesys/filesys.h ../filesys/filemanager.h
utility.o: ../threads/utility.cc ../threads/copyright.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/stdarg.h
threadtest.o: ../threads/threadtest.cc ../threads/copyright.h \
  ../threads/system.h ../threads/utility.h ../threads/bool.h \
  ../machine/sysdep.h ../threads/copyright.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/thread.h ../machine/machine.h \
  ../threads/utility.h ../machine/translate.h ../machine/disk.h \
  ../userprog/addrspace.h ../threads/copyright.h ../filesys/filesys.h \
  ../threads/copyright.h ../filesys/openfile.h ../threads/utility.h \
  ../userprog/memmanager.h ../threads/synch.h ../threads/list.h \
  ../userprog/bitmap.h ../threads/utility.h ../filesys/openfile.h \
  ../userprog/addrspace.h ../userprog/pcb.h ../threads/thread.h \
  ../threads/list.h ../filesys/filemanager.h ../userprog/bitmap.h \
  ../threads/synch.h ../filesys/sysopenfile.h ../filesys/useropenfile.h \
  ../threads/scheduler.h ../machine/interrupt.h ../threads/list.h \
  ../machine/stats.h ../machine/timer.h ../filesys/filesys.h \
  ../filesys/filemanager.h ../threads/synch.h
interrupt.o: ../machine/interrupt.cc ../threads/copyright.h \
  ../machine/interrupt.h ../threads/list.h ../threads/copyright.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/system.h ../threads/thread.h \
  ../machine/machine.h ../threads/utility.h ../machine/translate.h \
  ../machine/disk.h ../userprog/addrspace.h ../threads/copyright.h \
  ../filesys/filesys.h ../threads/copyright.h ../filesys/openfile.h \
  ../threads/utility.h ../userprog/memmanager.h ../threads/synch.h \
  ../threads/list.h ../userprog/bitmap.h ../threads/utility.h \
  ../filesys/openfile.h ../userprog/addrspace.h ../userprog/pcb.h \
  ../threads/thread.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h ../threads/scheduler.h ../machine/interrupt.h \
  ../machine/stats.h ../machine/timer.h ../filesys/filesys.h \
  ../filesys/filemanager.h
sysdep.o: ../machine/sysdep.cc ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/stdlib.h \
  /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
  /usr/include/endian.h /usr/include/bits/endian.h /usr/include/xlocale.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
  /usr/include/string.h /usr/include/signal.h /usr/include/bits/signum.h \
  /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h \
  /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h \
  /usr/include/sys/time.h /usr/include/sys/socket.h \
  /usr/include/sys/uio.h /usr/include/bits/uio.h \
  /usr/include/bits/socket.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/limits.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/bits/xopen_lim.h \
  /usr/include/bits/sockaddr.h /usr/include/asm/socket.h \
  /usr/include/asm/sockios.h /usr/include/sys/file.h /usr/include/fcntl.h \
  /usr/include/bits/fcntl.h /usr/include/sys/stat.h \
  /usr/include/bits/stat.h /usr/include/sys/un.h /usr/include/sys/mman.h \
  /usr/include/bits/mman.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
  /usr/include/bits/confname.h /usr/include/getopt.h \
  ../machine/interrupt.h ../threads/list.h ../threads/copyright.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  ../threads/system.h ../threads/thread.h ../machine/machine.h \
  ../threads/utility.h ../machine/translate.h ../machine/disk.h \
  ../userprog/addrspace.h ../threads/copyright.h ../filesys/filesys.h \
  ../threads/copyright.h ../filesys/openfile.h ../threads/utility.h \
  ../userprog/memmanager.h ../threads/synch.h ../threads/list.h \
  ../userprog/bitmap.h ../threads/utility.h ../filesys/openfile.h \
  ../userprog/addrspace.h ../userprog/pcb.h ../threads/thread.h \
  ../threads/list.h ../filesys/filemanager.h ../userprog/bitmap.h \
  ../threads/synch.h ../filesys/sysopenfile.h ../filesys/useropenfile.h \
  ../threads/scheduler.h ../machine/interrupt.h ../machine/stats.h \
  ../machine/timer.h ../filesys/filesys.h ../filesys/filemanager.h
stats.o: ../machine/stats.cc ../threads/copyright.h ../threads/utility.h \
  ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/stats.h
timer.o: ../machine/timer.cc ../threads/copyright.h ../machine/timer.h \
  ../threads/utility.h ../threads/copyright.h ../threads/bool.h \
  ../machine/sysdep.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/system.h ../threads/utility.h \
  ../threads/thread.h ../machine/machine.h ../machine/translate.h \
  ../machine/disk.h ../userprog/addrspace.h ../threads/copyright.h \
  ../filesys/filesys.h ../threads/copyright.h ../filesys/openfile.h \
  ../threads/utility.h ../userprog/memmanager.h ../threads/synch.h \
  ../threads/list.h ../userprog/bitmap.h ../threads/utility.h \
  ../filesys/openfile.h ../userprog/addrspace.h ../userprog/pcb.h \
  ../threads/thread.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h ../threads/scheduler.h ../machine/interrupt.h \
  ../threads/list.h ../machine/stats.h ../machine/timer.h \
  ../filesys/filesys.h ../filesys/filemanager.h
addrspace.o: ../userprog/addrspace.cc ../threads/copyright.h \
  ../threads/system.h ../threads/copyright.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/thread.h ../machine/machine.h \
  ../threads/utility.h ../machine/translate.h ../machine/disk.h \
  ../userprog/addrspace.h ../filesys/filesys.h ../threads/copyright.h \
  ../filesys/openfile.h ../threads/utility.h ../userprog/memmanager.h \
  ../threads/synch.h ../threads/list.h ../userprog/bitmap.h \
  ../threads/utility.h ../filesys/openfile.h ../userprog/addrspace.h \
  ../userprog/pcb.h ../threads/thread.h ../threads/list.h \
  ../filesys/filemanager.h ../userprog/bitmap.h ../threads/synch.h \
  ../filesys/sysopenfile.h ../filesys/useropenfile.h \
  ../threads/scheduler.h ../machine/interrupt.h ../threads/list.h \
  ../machine/stats.h ../machine/timer.h ../filesys/filesys.h \
  ../filesys/filemanager.h ../userprog/pcbmanager.h ../bin/noff.h
bitmap.o: ../userprog/bitmap.cc ../threads/copyright.h \
  ../userprog/bitmap.h ../threads/utility.h ../threads/copyright.h \
  ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../filesys/openfile.h ../threads/copyright.h \
  ../threads/utility.h
memmanager.o: ../userprog/memmanager.cc ../userprog/memmanager.h \
  ../threads/synch.h ../threads/copyright.h ../threads/thread.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/machine.h ../threads/utility.h \
  ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
  ../threads/copyright.h ../filesys/filesys.h ../threads/copyright.h \
  ../filesys/openfile.h ../threads/utility.h ../userprog/pcb.h \
  ../threads/thread.h ../userprog/bitmap.h ../threads/utility.h \
  ../filesys/openfile.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h ../threads/list.h ../userprog/addrspace.h \
  ../machine/machine.h
pcb.o: ../userprog/pcb.cc ../userprog/pcb.h ../threads/thread.h \
  ../threads/copyright.h ../threads/utility.h ../threads/bool.h \
  ../machine/sysdep.h ../threads/copyright.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/machine.h ../threads/utility.h \
  ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
  ../threads/copyright.h ../filesys/filesys.h ../threads/copyright.h \
  ../filesys/openfile.h ../threads/utility.h ../userprog/memmanager.h \
  ../threads/synch.h ../threads/thread.h ../threads/list.h \
  ../userprog/bitmap.h ../threads/utility.h ../filesys/openfile.h \
  ../userprog/addrspace.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h
pcbmanager.o: ../userprog/pcbmanager.cc /usr/include/string.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/xlocale.h ../userprog/pcbmanager.h ../threads/synch.h \
  ../threads/copyright.h ../threads/thread.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/bits/types.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
  ../machine/machine.h ../threads/utility.h ../machine/translate.h \
  ../machine/disk.h ../userprog/addrspace.h ../threads/copyright.h \
  ../filesys/filesys.h ../threads/copyright.h ../filesys/openfile.h \
  ../threads/utility.h ../userprog/memmanager.h ../userprog/bitmap.h \
  ../threads/utility.h ../filesys/openfile.h ../userprog/addrspace.h \
  ../userprog/pcb.h ../threads/thread.h ../threads/list.h \
  ../filesys/filemanager.h ../userprog/bitmap.h ../threads/synch.h \
  ../filesys/sysopenfile.h ../filesys/useropenfile.h ../threads/list.h
exception.o: ../userprog/exception.cc /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/copyright.h ../threads/system.h \
  ../threads/copyright.h ../threads/utility.h ../threads/bool.h \
  ../machine/sysdep.h ../threads/copyright.h ../threads/thread.h \
  ../machine/machine.h ../threads/utility.h ../machine/translate.h \
  ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
  ../threads/copyright.h ../filesys/openfile.h ../threads/utility.h \
  ../userprog/memmanager.h ../threads/synch.h ../threads/list.h \
  ../userprog/bitmap.h ../threads/utility.h ../filesys/openfile.h \
  ../userprog/addrspace.h ../userprog/pcb.h ../threads/thread.h \
  ../threads/list.h ../filesys/filemanager.h ../userprog/bitmap.h \
  ../threads/synch.h ../filesys/sysopenfile.h ../filesys/useropenfile.h \
  ../threads/scheduler.h ../machine/interrupt.h ../threads/list.h \
  ../machine/stats.h ../machine/timer.h ../filesys/filesys.h \
  ../filesys/filemanager.h ../userprog/syscall.h ../userprog/pcbmanager.h
progtest.o: ../userprog/progtest.cc ../threads/copyright.h \
  ../threads/system.h ../threads/copyright.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/thread.h ../machine/machine.h \
  ../threads/utility.h ../machine/translate.h ../machine/disk.h \
  ../userprog/addrspace.h ../filesys/filesys.h ../threads/copyright.h \
  ../filesys/openfile.h ../threads/utility.h ../userprog/memmanager.h \
  ../threads/synch.h ../threads/list.h ../userprog/bitmap.h \
  ../threads/utility.h ../filesys/openfile.h ../userprog/addrspace.h \
  ../userprog/pcb.h ../threads/thread.h ../threads/list.h \
  ../filesys/filemanager.h ../userprog/bitmap.h ../threads/synch.h \
  ../filesys/sysopenfile.h ../filesys/useropenfile.h \
  ../threads/scheduler.h ../machine/interrupt.h ../threads/list.h \
  ../machine/stats.h ../machine/timer.h ../filesys/filesys.h \
  ../filesys/filemanager.h ../machine/console.h
sysopenfile.o: ../filesys/sysopenfile.cc ../filesys/sysopenfile.h \
  ../filesys/openfile.h ../threads/copyright.h ../threads/utility.h \
  ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
  ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h
useropenfile.o: ../filesys/useropenfile.cc ../filesys/useropenfile.h \
  /usr/include/string.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/xlocale.h
filemanager.o: ../filesys/filemanager.cc ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/copyright.h ../threads/utility.h \
  ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
  ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../filesys/openfile.h ../threads/copyright.h \
  ../threads/utility.h ../threads/synch.h ../threads/thread.h \
  ../threads/utility.h ../machine/machine.h ../threads/utility.h \
  ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
  ../filesys/filesys.h ../filesys/openfile.h ../userprog/memmanager.h \
  ../threads/synch.h ../userprog/bitmap.h ../userprog/addrspace.h \
  ../userprog/pcb.h ../threads/thread.h ../threads/list.h \
  ../filesys/filemanager.h ../filesys/useropenfile.h ../threads/list.h \
  ../filesys/sysopenfile.h
console.o: ../machine/console.cc ../threads/copyright.h \
  ../machine/console.h ../threads/utility.h ../threads/copyright.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/system.h ../threads/utility.h \
  ../threads/thread.h ../machine/machine.h ../machine/translate.h \
  ../machine/disk.h ../userprog/addrspace.h ../threads/copyright.h \
  ../filesys/filesys.h ../threads/copyright.h ../filesys/openfile.h \
  ../threads/utility.h ../userprog/memmanager.h ../threads/synch.h \
  ../threads/list.h ../userprog/bitmap.h ../threads/utility.h \
  ../filesys/openfile.h ../userprog/addrspace.h ../userprog/pcb.h \
  ../threads/thread.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h ../threads/scheduler.h ../machine/interrupt.h \
  ../threads/list.h ../machine/stats.h ../machine/timer.h \
  ../filesys/filesys.h ../filesys/filemanager.h
machine.o: ../machine/machine.cc ../threads/copyright.h \
  ../machine/machine.h ../threads/utility.h ../threads/copyright.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/translate.h ../machine/disk.h \
  ../threads/system.h ../threads/utility.h ../threads/thread.h \
  ../machine/machine.h ../userprog/addrspace.h ../threads/copyright.h \
  ../filesys/filesys.h ../threads/copyright.h ../filesys/openfile.h \
  ../threads/utility.h ../userprog/memmanager.h ../threads/synch.h \
  ../threads/list.h ../userprog/bitmap.h ../threads/utility.h \
  ../filesys/openfile.h ../userprog/addrspace.h ../userprog/pcb.h \
  ../threads/thread.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h ../threads/scheduler.h ../machine/interrupt.h \
  ../threads/list.h ../machine/stats.h ../machine/timer.h \
  ../filesys/filesys.h ../filesys/filemanager.h
mipssim.o: ../machine/mipssim.cc ../threads/copyright.h \
  ../machine/machine.h ../threads/utility.h ../threads/copyright.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/translate.h ../machine/disk.h \
  ../machine/mipssim.h ../threads/system.h ../threads/utility.h \
  ../threads/thread.h ../machine/machine.h ../userprog/addrspace.h \
  ../threads/copyright.h ../filesys/filesys.h ../threads/copyright.h \
  ../filesys/openfile.h ../threads/utility.h ../userprog/memmanager.h \
  ../threads/synch.h ../threads/list.h ../userprog/bitmap.h \
  ../threads/utility.h ../filesys/openfile.h ../userprog/addrspace.h \
  ../userprog/pcb.h ../threads/thread.h ../threads/list.h \
  ../filesys/filemanager.h ../userprog/bitmap.h ../threads/synch.h \
  ../filesys/sysopenfile.h ../filesys/useropenfile.h \
  ../threads/scheduler.h ../machine/interrupt.h ../threads/list.h \
  ../machine/stats.h ../machine/timer.h ../filesys/filesys.h \
  ../filesys/filemanager.h
translate.o: ../machine/translate.cc ../threads/copyright.h \
  ../machine/machine.h ../threads/utility.h ../threads/copyright.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i486-linux-gnu/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/translate.h ../machine/disk.h \
  ../userprog/addrspace.h ../threads/copyright.h ../filesys/filesys.h \
  ../threads/copyright.h ../filesys/openfile.h ../threads/utility.h \
  ../userprog/memmanager.h ../threads/synch.h ../threads/thread.h \
  ../threads/utility.h ../machine/machine.h ../userprog/addrspace.h \
  ../threads/list.h ../userprog/bitmap.h ../threads/utility.h \
  ../filesys/openfile.h ../userprog/addrspace.h ../userprog/pcb.h \
  ../threads/thread.h ../threads/list.h ../filesys/filemanager.h \
  ../userprog/bitmap.h ../threads/synch.h ../filesys/sysopenfile.h \
  ../filesys/useropenfile.h ../threads/system.h ../threads/scheduler.h \
  ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
  ../machine/timer.h ../filesys/filesys.h ../filesys/filemanager.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
