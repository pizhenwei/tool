#include <stdio.h>


union cpuid10_eax {
	struct {
		unsigned int version_id:8;
		unsigned int num_counters:8;
		unsigned int bit_width:8;
		unsigned int mask_length:8;
	} split;
	unsigned int full;
};


static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
		unsigned int *ecx, unsigned int *edx)
{
	/* ecx is often an input as well as an output. */
	asm volatile("cpuid"
			: "=a" (*eax),
			"=b" (*ebx),
			"=c" (*ecx),
			"=d" (*edx)
			: "0" (*eax), "2" (*ecx)
			: "memory");
}


static inline void cpuid(unsigned int op,
		unsigned int *eax, unsigned int *ebx,
		unsigned int *ecx, unsigned int *edx)
{
	*eax = op;
	*ecx = 0;
	native_cpuid(eax, ebx, ecx, edx);
}



int main()
{
	unsigned int ebx, ecx, edx;
	union cpuid10_eax eax;

	cpuid(10, &eax.full, &ebx, &ecx, &edx);

	printf("PMU counters : %d\n", eax.split.num_counters);
}
