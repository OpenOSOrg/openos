#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/* This function is intended so simulate a thread needing to do some other 
 * work in between output statements.
 */
static long waste_cpu()
{
    long dummy = 0;
    for (int i = 0; i < 10000; i++) {
        dummy += rand();
    }
    return dummy;
}

/* Start of function executed by each thread.
 * Each character of the argument string is printed out one-by-one
 * in a separate system call. 
 * To increase the number of interleavings, we voluntarily yield the 
 * CPU after each character is output.
 */
static void *write_one_by_one(void *arg)
{
    char *mystr = (char *)arg;
      
    for (int i = 0; i < strlen(mystr); i++) {
        write(STDOUT_FILENO, &mystr[i], 1); 
        waste_cpu();
    }
  
    return (void *)0;       
}
/* End of function executed by each thread. */


int main(int argc, char **argv)
{
    pthread_t tid1, tid2;
    char *str1 = "Hello";
    char *str2 = "Goodbye";

    /* Normally we'd want to test the return value of pthread_create. */

    (void)pthread_create(&tid1, NULL, write_one_by_one, (void *)str1 );
    (void)pthread_create(&tid2, NULL, write_one_by_one, (void *)str2 );

    /* Wait for child threads to finish */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    write(STDOUT_FILENO, "\n", 1);    
    return 0;
}

