# Shells and system calls

When debugging a process that forks with GDB, you can debug parent, debug children or all processes.  Lets do a simple example of a simple program that forks, and where parent has a simple signal handler to block waiting for the child. 

Some handy commands
   - info inferiors - print list of all inferiors being managed
   - inferior X - switch to debugging X
   - follow-fork-mode (show, set) 
      - e.g., **set follow-fork-mode child** to follow child instead of parent
   - detach-on-fork (on - one, off - both)
      - e.g., **set detach-on-fork off** to debug all the processes
      - note, you are debugging one at a time, and child is blocked right after fork

For more information, see [here](https://sourceware.org/gdb/onlinedocs/gdb/Forks.html)
