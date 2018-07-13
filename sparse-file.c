#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SEQUENCE 10000
#define BLOCKSIZE 4096
#define HOLESIZE 4096
#define TOTALSIZE (4096*1024*1024UL)

char *output = "output";

void die(char *s)
{
	perror(s);
	exit(1);
}

void usage() {
	printf("Usage :\n");
	printf("\t-h : show help message\n");
	printf("\t-s : block size, default %d\n", BLOCKSIZE);
	printf("\t-l : hole size, default %d\n", HOLESIZE);
	printf("\t-t : total size, default %ld\n", TOTALSIZE);
	printf("\t-o : output file name, default %s\n", output);

	exit(0);
}

int main(int argc, char *argv[])
{
	char *buf = NULL;
	long block_size = BLOCKSIZE;
	long hole_size = HOLESIZE;
	long total_size = TOTALSIZE;
	int output_fd = 0;
	int opt = 0;

	while ((opt = getopt(argc, argv, "hs:l:t:o:")) != -1) {
		switch (opt) {
			case 's':
				block_size = atoll(optarg);
				break;

			case 'l':
				hole_size = atoll(optarg);
				break;

			case 't':
				total_size = atoll(optarg);
				break;

			case 'o':
				output = optarg;
				break;

			case 'h':
			default :
				usage();
		}
	}

	if ((output_fd = open(output, O_CREAT | O_RDWR, 0644)) == -1)
		die("open");

	printf("open %s, prepare to write block %ld and hole %ld ...\n", output, block_size, hole_size);

	buf = calloc(1, block_size);
	if (buf == NULL)
		die("malloc");

	long blocks = 0;
	long wrote = 0;
	for (wrote = 0; wrote < total_size; ) {
		size_t ret = 0;
		ret = pwrite(output_fd, buf, block_size, wrote);
		if (ret < 0)
			die("write");

		wrote = wrote + block_size + hole_size;
		blocks++;
	}

	printf("write %s success, %ld blocks\n", output, blocks);

	fsync(output_fd);
	close(output_fd);

	return 0;
}
