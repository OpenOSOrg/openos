#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static void *write_all(void *arg)
{
    int num_yield = rand() % 100;
    char *mystr = (char *)arg;
   
    for (int i = 0; i < num_yield; i++) {
        sched_yield();
    }
		        
    write(STDOUT_FILENO, mystr, strlen(mystr));
    return (void *)0;
}


static void *write_one_by_one(void *arg)
{
    char *mystr = (char *)arg;
     long dummy = 0; 
    for (int i = 0; i < strlen(mystr); i++) {
        write(STDOUT_FILENO, &mystr[i], 1); 
	//usleep(10);
	//sched_yield();
	for (int i = 0; i < 100000; i++) {
		dummy += rand();
        }
    }
  
    return (void *)dummy;
		        
}

static void *waste_cpu(void *arg)
{
	long dummy = (long)arg;
	for (int i = 0; i < 1000000; i++) {
		dummy += rand();
        }
	return (void*)dummy;
}

int main(int argc, char **argv)
{
    pthread_t tid1, tid2;
    char *str1 = "Hello";
    char *str2 = "Goodbye";
	
    int nspinners = 0;
    pthread_t spinner_tids[nspinners];

    for (int i = 0; i < nspinners; i++) {
	(void)pthread_create(&spinner_tids[i], NULL, waste_cpu, NULL);
    }

    /* 1. Each thread writes out its string in a single system call. */
    
    /*
     *     * Normally we'd want to test the return value of pthread_create. 
     */
    (void)pthread_create(&tid1, NULL, write_all, (void *)str1 );
    (void)pthread_create(&tid2, NULL, write_all, (void *)str2 );

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
			
    write(STDOUT_FILENO, "\n", 1);    
    /* 2. Each thread writes out its string one character at a time using multiple system calls.*/
    (void)pthread_create(&tid1, NULL, write_one_by_one, (void *)str1 );
    (void)pthread_create(&tid2, NULL, write_one_by_one, (void *)str2 );

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
	        
	for (int i = 0; i < nspinners; i++) {
		pthread_join(spinner_tids[i], NULL);
	}
    return 0;
}

