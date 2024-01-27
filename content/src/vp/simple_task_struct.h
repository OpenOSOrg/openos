struct task_struct {
  // the state of the task: running, blocked, runable
  unsigned int  __state;

  // CPU-specific state of this task
  struct thread_struct            thread;

  // a pointer to the memory management data structures
  struct mm_struct                *mm;

  // Open file information 
  struct files_struct             *files;
}
