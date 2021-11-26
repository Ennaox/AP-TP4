#include <math.h>
#include <stdio.h>
#include <stdint.h>

#define ALLIGN 64

uint64_t rdtsc()
{
	uint64_t tsc;
	__asm__ volatile ("rdtsc": "=A" (tsc));
	return tsc;
}

double pearson_correlation(double * restrict x, double * restrict y,uint64_t array_size)
{
	double top, bot;
	double sum1 = 0;
	double sum2 = 0;
	double sum3 = 0;
	for(uint64_t i = 0; i<array_size; i++)
	{
		sum1 += x[i] * y[i];
	}
	for(uint64_t i = 0; i<array_size; i++)
	{
		sum2 += x[i];
	}

	for(uint64_t i = 0; i<array_size; i++)
	{
		sum3 += y[i];
	}

	sum2 *= sum3;
	sum1 -= sum2;
	top = sum1;
	

}

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Error: wrong number of arguments\nUsage: %s [array size]\n", argv[0]);
		return 1;
	}
	array_size = atoll(argv[1]);

	srand(getpid());

	double * restrict x = aligned_alloc(ALLIGN,array_size * sizeof(double));
	double * restrict y = aligned_alloc(ALLIGN,array_size * sizeof(double));

	for(int i = 0; i<array_size; i++)
	{
		x[i] = (rand()%1000)/(rand()%100);
		y[i] = (rand()%1000)/(rand()%100);
	}

	uint64_t before = rdtsc();
	result = pearson_correlation(x,y,array_size);
	uint64_t after = rdtsc();

	free(x);
	free(y);

	printf("result: %lf rdtsc: %lu nb_bytes: %s\n", result,after-before,array_size * sizeof(double));
	return 0;
}