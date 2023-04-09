
struct wait_queue {
	/* list of thread ids */
	int dummy;
};

void wq_sleep(struct wait_queue *wq) 
{
	/* Suspend the calling thread, recording its id in the given wait_queue structure. */
}

void wq_wakeup(struct wait_queue *wq) 
{
	/* Remove the first thread from the given wait_queue structure and make it runnable. */
}

void wq_wakeup_all(struct wait_queue *wq)
{
	/* Remove all threads from the given wait_queue structure and make them runnable. */
}
