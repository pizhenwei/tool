#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help()
{
	printf("Usage :\n");
	printf("\t-s SIZE : size[MB]\n");
	printf("\t-c CHAR : fill char\n");
	printf("\t-d      : fill different data\n");
	printf("\t-z      : fill zero\n");
}


int main(int argc, char *argv[])
{
	unsigned long size = 1024 * 1024 * 1024UL;
	unsigned long value = 0;
	unsigned long *addr = NULL;
	int opt, fillzero = 0, filldiff = 0;
	char fillchar = 0;

	while ((opt = getopt(argc, argv, "hs:c:dz")) != -1) {
		switch (opt) {
			case 's':
				size = atoi(optarg) * 1024 * 1024UL;
				break;

			case 'c' :
				fillchar = *optarg;
				break;

			case 'd':
				filldiff = 1;
				break;

			case 'z':
				fillzero = 1;
				break;

			case 'h':
			default:
				show_help();
				return 0;
		}
	}

	addr = (unsigned long*)mmap(NULL, size,
			PROT_READ | PROT_EXEC | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
			-1, 0);

	if (fillzero) {
		memset(addr, 0x00, size);
	} else if (fillchar) {
		memset(addr, fillchar, size);
	} else if (filldiff) {
		for (value = 0; value < size;) {
			addr[value/8] = value;
			value += 8;
		}
	}

	munmap(addr, size);

	return 0;
}

