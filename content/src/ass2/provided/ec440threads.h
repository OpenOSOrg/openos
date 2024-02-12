#ifndef __EC440THREADS__
#define __EC440THREADS__
/*
 * This file is derived from code provided by Prof. Egele 
 */


/*
 * You should use:
 *    - setjmp to save registers of current thread
 *    - longjump to restore registers of thread you are context switching to
 * These routines store the registers in a mangled fashion, and hide 
 * where different registers are. You can use:
 *    - the enum jump_buffer_location to identify where the register is in the buffer
 *    - the functions set_reg and get_reg to set and retrieve registers from this buffer
 * e.g. 
 *   jmp_buf buf;
 *   setjmp(buf); 
 *   pc = get_reg(buf, JBL_PC);
 *   pc = (unsigned long int)foo;  (where foo is a function you want to call)
 *   set_reg(buf, JBL_PC, pc);
 */

/* 
 * Jump buffer location: 
 * These constants define for current implementation of system libraries on our container
 * the registers held in various locations in the jump buffer when you call setjmp.
 * Note, these are not part of the public interface for jmp_buf, but are extracted from 
 * internal private libc headers here: https://github.com/nerc-project/operations/issues/288
 */
enum JBL
  {
   JBL_RBX = 0,
   JBL_RBP = 1,
   JBL_R12 = 2, 
   JBL_R13 = 3,
   JBL_R14 = 4,
   JBL_R15 = 5,
   JBL_RSP = 6,
   JBL_PC  = 7
  };


/* 
 * Unfortunately, there is a complication on the Linux systems in the
 * student/grading environment. These machines are equipped with a
 * libc that includes a security feature to protect the addresses
 * stored in jump buffers. This feature "mangles" a pointer before
 * saving it in a jmp_buf.
*/
static unsigned long int _ptr_demangle(unsigned long int p)
{
    unsigned long int ret;

    asm("movq %1, %%rax;\n"
        "rorq $0x11, %%rax;"
        "xorq %%fs:0x30, %%rax;"
        "movq %%rax, %0;"
    : "=r"(ret)
    : "r"(p)
    : "%rax"
    );
    return ret;
}

static unsigned long int _ptr_mangle(unsigned long int p)
{
    unsigned long int ret;

    asm("movq %1, %%rax;\n"
        "xorq %%fs:0x30, %%rax;"
        "rolq $0x11, %%rax;"
        "movq %%rax, %0;"
    : "=r"(ret)
    : "r"(p)
    : "%rax"
    );
    return ret;
}

static void set_reg(jmp_buf *buf, enum JBL reg, unsigned long int val)
{
  switch (reg) {
  case JBL_RBX:
  case JBL_RBP:
  case JBL_RSP:
  case JBL_PC:
    (*buf)->__jmpbuf[reg] = _ptr_mangle(val);
    return; 
  case JBL_R12:
  case JBL_R13:
  case JBL_R14:
  case JBL_R15:
    (*buf)->__jmpbuf[reg] = val;
    return;
  }
  assert(0);
}

static unsigned long int get_reg(jmp_buf *buf, enum JBL reg)
{
  switch (reg) {
  case JBL_RBX:
  case JBL_RBP:
  case JBL_RSP:
  case JBL_PC:
    return _ptr_demangle((*buf)->__jmpbuf[reg]);
  case JBL_R12:
  case JBL_R13:
  case JBL_R14:
  case JBL_R15:
    return (*buf)->__jmpbuf[reg];
  }
  assert(0);
  return -1;
}


/* 
 * Setting registers for a new thread:
 * When creating a new thread that will begin in start_routine, we
 * also need to ensure that `arg` is passed to the start_routine.
 * We cannot simply store `arg` in a register and set PC=start_routine.
 * This is because the AMD64 calling convention keeps the first arg in
 * the EDI register, which is not a register we control in jmp_buf.
 * We provide a start_thunk function that copies R13 to RDI then jumps
 * to R12, effectively calling function_at_R12(value_in_R13). So
 * you can call your start routine with the given argument by setting
 * your new thread's PC to be ptr_mangle(start_thunk), and properly
 * assigning R12 and R13.
*/
static void *start_thunk() {
  asm("popq %%rbp;\n"           //clean up the function prologue
      "movq %%r13, %%rdi;\n"    //put arg in $rdi
      "pushq %%r12;\n"          //push &start_routine
      "retq;\n"                 //return to &start_routine
      :
      :
      : "%rdi"
  );
  __builtin_unreachable();
}


// to supress compiler error say these static functions may not be used...
static unsigned long int _ptr_mangle(unsigned long int p)__attribute__((unused));
static unsigned long int _ptr_demangle(unsigned long int p)__attribute__((unused));

static void set_reg(jmp_buf *buf, enum JBL reg, unsigned long int val)__attribute__((unused));
static unsigned long int get_reg(jmp_buf *buf, enum JBL reg)__attribute__((unused));
static void *start_thunk() __attribute__((unused));


#endif
