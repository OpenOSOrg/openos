## Programs
- simplefork: parent starts a bunch of children; children start & sleep, parent's signal handler registers them
- wo - also generates wo-static - is a simple program that runs forever to let you look at the sections in a simple program and the corresponding regions in the virtual memory
   - ``` objdump -h wo```: look at sections at the beginning
   - ``` objdump -h wo-static```: look at sections at the beginning
   - ``` ps -f``` to get pid of wo-static and ```cat /proc/PID/maps```
   - debug using ```gdb wo -p PID``` and type ```disassemble``` to find the address for the code
- zombie - child sleeps for a long time, if you type ps -f, you see it is defunct, but has not been waited for
- forkoff - starts a whole bunch of children and parent exits
  ```./forkoff & ps -f ; sleep 10 ; ps -f ```: note change in PPID
  ```ps -ejH ```: print out tree
  ```ps -f```: show PPID
  ``ps | grep forkoff | awk '{print $1}' | xargs kill```: kill all the processes with name forkoff


## Notes on debugging multiple processes
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
