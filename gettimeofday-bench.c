#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <stdio.h>

#define LOOP 10000000

static inline unsigned long rdtsc(void)
{
	unsigned long low, high;

	asm volatile("rdtsc" : "=a" (low), "=d" (high) );

	return ((low) | (high) << 32);
}

void show_tv(struct timeval *tv, char *prefix)
{
	printf("[%s]sec = %ld, usec = %ld\n", prefix, tv->tv_sec, tv->tv_usec);
}

int main()
{
	long loop;
	struct timeval tmp;
	unsigned long start, end, elapsed;
	int (*__gettimeofday)(struct timeval *, struct timezone *);
	__gettimeofday = 0xffffffffff600000;

	gettimeofday(&tmp, NULL);
	show_tv(&tmp, "VDSO");

	syscall(SYS_gettimeofday, &tmp, NULL);
	show_tv(&tmp, "SYSCALL");

	__gettimeofday(&tmp, NULL);
	show_tv(&tmp, "VSYSCALL");

	start = rdtsc();
	for (loop = 0; loop < LOOP; loop++) {
		gettimeofday(&tmp, NULL);
	}
	end = rdtsc();

	elapsed = end - start;
	printf("VDSO gettimeofday test %ld cycles, everage %ld cycles\n", elapsed, elapsed / LOOP);

	start = rdtsc();
	for (loop = 0; loop < LOOP; loop++) {
		syscall(SYS_gettimeofday, &tmp, NULL);
	}
	end = rdtsc();

	elapsed = end - start;
	printf("SYSCALL gettimeofday test %ld cycles, everage %ld cycles\n", elapsed, elapsed / LOOP);

	start = rdtsc();
	for (loop = 0; loop < LOOP; loop++) {
		__gettimeofday(&tmp, NULL);
	}
	end = rdtsc();

	elapsed = end - start;
	printf("VSYSCALL gettimeofday test %ld cycles, everage %ld cycles\n", elapsed, elapsed / LOOP);

	return 0;
}

