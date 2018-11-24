#include <stdio.h>


static inline unsigned long long rdtsc(void)
{
    unsigned long low, high;
    asm volatile("rdtsc" : "=a" (low), "=d" (high) );

    return ((low) | (high) << 32);
}


#define CPUPAUSELOOP "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"\
    "pause\n"


void bench(int loops, unsigned long rdtsc_cycles)
{
    int i = 0;

    for (i = 0; i < loops; i++) {
        unsigned long start, finish, elapsed;

        start = rdtsc();

        asm(
                CPUPAUSELOOP
                CPUPAUSELOOP
                CPUPAUSELOOP
                CPUPAUSELOOP
                CPUPAUSELOOP
                ::
                :);

        finish = rdtsc();

        elapsed = finish - start - rdtsc_cycles;
        printf("total = %ld, average = %ld\n", elapsed, elapsed / 100);
    }
}

unsigned long benchrdtsc()
{
    unsigned long start, finish, elapsed;

    start = rdtsc();

    finish = rdtsc();
    finish = rdtsc();
    finish = rdtsc();
    finish = rdtsc();
    finish = rdtsc();

    finish = rdtsc();
    finish = rdtsc();
    finish = rdtsc();
    finish = rdtsc();
    finish = rdtsc();

    elapsed = finish - start;

    return elapsed / 10;
}


int main()
{
    unsigned long rdtsc_cycles = benchrdtsc();
    bench(10, rdtsc_cycles);

    return 0;
}
