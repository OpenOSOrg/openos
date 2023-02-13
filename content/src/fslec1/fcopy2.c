// simple program to copy a file

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>

#define BUF_SIZE 4096
// user has read and write permission

int main(int argc, char *argv[])
{
	int in_fd, out_fd, rd_count, wt_count, rc;
	mode_t md; 
	struct stat statbuf;	
	char buffer[BUF_SIZE];

	if (argc != 3) {
		perror("Can't open input file\n");
		exit(1);
	}

	in_fd = open(argv[1], O_RDONLY);
	if (in_fd < 0) {
		perror("Can't creat output file\n");
		exit(1);
	}
	if ((rc = fstat(in_fd, &statbuf)) <0) {
		perror("fstat failed\n");
		exit(1);
	}
	md = statbuf.st_mode & (S_IRWXU|S_IRWXG|S_IRWXO);

	out_fd = creat(argv[2], md);
	if (out_fd < 0) {
		perror("Can't creat output file\n");
		exit(1);
	}

	while(1) {
		rd_count = read(in_fd, buffer, BUF_SIZE);
		if (rd_count==0) { // done
			exit(0);
		}
		assert(rd_count > 0);

			
		wt_count = write(out_fd, buffer, rd_count);
		assert(wt_count == rd_count);
	}
	close(in_fd);
	close(out_fd);
}
