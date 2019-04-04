#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>

int main(int argc, char *argv[])
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("[Standard]\n\ttv_sec  = %24lu\n\ttv_usec = %24lu\n",
			tv.tv_sec, tv.tv_usec);

	printf("[Ns]\n\ttv_sec  = %24llu\n",
			tv.tv_sec * 1000000000LL + tv.tv_usec * 1000);

	return 0;
}
