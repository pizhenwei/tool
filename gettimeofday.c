#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>

int main(int argc, char *argv[])
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    printf("tv_sec  = %16lu\ntv_usec = %16lu\n", tv.tv_sec, tv.tv_usec);

    return 0;
}
