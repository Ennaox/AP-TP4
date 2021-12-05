#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define ALLIGN 64
#define NB_REP 100

uint64_t rdtsc()
{
	uint64_t tsc;
	__asm__ volatile ("rdtsc": "=A" (tsc));
	return tsc;
}

double pearson_correlation(double * restrict x, double * restrict y,uint64_t array_size)
{
	double bot = 0;
	double top = 0;
	double sum2 = 0;
	double sum3 = 0;
	double sum4 = 0;
	
	for(uint64_t i = 0; i<array_size; i++)
	{
		top += x[i] * y[i];
	}
	for(uint64_t i = 0; i<array_size; i++)
	{
		sum2 += x[i];
		bot += x[i] * x[i];
	}

	for(uint64_t i = 0; i<array_size; i++)
	{
		sum3 += y[i];
		sum4 += y[i] * y[i];
	}

	top -= sum3 * sum2;
		
	bot = (array_size * bot) - (sum2 * sum2);

	sum4 = (array_size * sum4) - (sum3 * sum3);
	bot = sqrt(bot) * sqrt(sum4);
	return top/bot;
}

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Error: wrong number of arguments\nUsage: %s [array size]\n", argv[0]);
		return 1;
	}
	int array_size = atoll(argv[1]);
	double result = 0;
	FILE* F = fopen("result.dat","w");

	srand(getpid());
	for(int arr = 0; arr<array_size; arr++)
	{
		printf("%d/%d\n", arr+1, array_size);
		double * restrict x = aligned_alloc(ALLIGN,arr * sizeof(double));
		double * restrict y = aligned_alloc(ALLIGN,arr * sizeof(double));
		uint64_t tt_tsc = 0;

		for(int i = 0; i<arr; i++)
		{
			x[i] = (rand()%10000)/((rand()%100)+1);
			y[i] = (rand()%10000)/((rand()%100)+1);
		}

		for(int rep = 0; rep<NB_REP; rep ++)
		{
			uint64_t before = rdtsc();
			result += pearson_correlation(x,y,arr);
			uint64_t after = rdtsc();
			tt_tsc += (after - before);
		}
		fprintf(F, "%lf %d\n",(double)tt_tsc/(double)NB_REP,arr);
		free(x);
		free(y);
	
	}
	fclose(F);
	printf("%lf\n",result);
	return 0;
}