#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>

char template1[] = "chk/in.XXXXXX";
char template2[] = "chk/out.XXXXXX"; 

struct args_s {
    int id;
    char *infile;
    char *outfile;
};

/* Thread function -- livelocks if open file limit is too low. */
void *threadfunc(void *arg)
{
    struct args_s *my_args = (struct args_s *)arg;

    int fd_in;
    int fd_out;

    /* Open input file, retrying if there are too many files already open */
    for ( ; ; ) {
        fd_in = open(my_args->infile, O_RDONLY);
        if (fd_in > 0) {
            break;
        }
        if (errno != EMFILE) {
            return NULL;
        }
    }

    fprintf(stderr,"Thread %d has input file %s open now.\n", 
            my_args->id, my_args->infile);

    /* Open output file, retrying if there are too many files already open */
    for ( ; ; ) {
        fd_out = open(my_args->outfile, O_RDWR);
        if (fd_out > 0) {
            break;
        }
        if (errno != EMFILE)  {
            close(fd_in);
            return NULL;
        }
    }
    fprintf(stderr,"Thread %d has output file %s open now.\n",
            my_args->id, my_args->outfile);

    /* Sleep for a while to simulate time reading input and producing output */
    sleep(1);

    close(fd_in);
    close(fd_out);

    return NULL;
}
/* End of thread function */

int main(int argc, char **argv)
{
    int num_created = 0;
    int i;
    pthread_t ids[16];
    struct args_s *targs[16];
    char *tmpname = (char *)malloc(20);

    /* Create all the input and output files before creating any threads */
    for (i=0; i < 16; i++) {
        targs[i] = (struct args_s *)malloc(sizeof(struct args_s));
        targs[i]->id = i;
        memset(tmpname, 0, 20);
        strncpy(tmpname, template1, 20);
        int fd = mkstemp(tmpname);
        if (fd < 0) {
            perror("main thread mkstemp infile");
            break;
        }
        close(fd);
        targs[i]->infile = (char *)malloc(strlen(tmpname)+1);
        strncpy(targs[i]->infile, tmpname, strlen(tmpname)+1);

        memset(tmpname, 0, 20);
        strncpy(tmpname, template2, 20);
        fd = mkstemp(tmpname);
        if (fd < 0) {
            perror("main thread mkstmp outfile");
            break;
        }
        close(fd);
        targs[i]->outfile = (char *)malloc(strlen(tmpname)+1);
        strncpy(targs[i]->outfile, tmpname, strlen(tmpname)+1);
    }

    for (i=0; i < 16; i++) {
        /* Create the thread, passing input and output names */
        pthread_create(&ids[i], NULL, threadfunc, (void *)targs[i]);
    }

    for (i = 0; i < 16; i++) {
        pthread_join(ids[i], 0);
    }

        
}

