#include "profiler.h"
#include <string.h>

#define num_runs 100
#define num_iter 1
#define fnc	4

// Switch to enums
#define fn0 ft_memcpy
#define fn1 ft_bytecpy
#define fn2 memcpy
#define fn3 ft_memcpy2

static float	resf = 0.0f;
static int32_t	resi = 0;
static int64_t	resl = 0;

void	*ft_memcpy(void *restrict dst_void, const void *restrict src_void, size_t length);
void	*ft_bytecpy(void *dst_void, const void *src_void, size_t length);
void	*ft_memcpy2(void *dst_void, const void *src_void, size_t length);

void	res_set(void)
{
	resf = 0.0001f;
	resi = 1;
	resl = 0;
}

#define array_len 4000
uint64_t benchmark_rng(uint32_t fn_index)
{
	res_set();
	char dst[array_len];
	char src[array_len];

	for (size_t i=0;i<array_len;i++)
		src[i] = (uint8_t) rand();
	uint64_t start = ns();
	switch (fn_index)
	{
		case 0:
			for (uint64_t i = 0; i < num_iter; i++)
				fn0(dst, src, array_len);
			break;
		case 1:
			for (uint64_t i = 0; i < num_iter; i++)
				fn1(dst, src, array_len);
			break;
		case 2:
			for (uint64_t i = 0; i < num_iter; i++)
				fn2(dst, src, array_len);
			break;
		case 3:
			for (uint64_t i = 0; i < num_iter; i++)
				fn3(dst, src, array_len);
			break;
		default:
			break;
	}
	return (ns() - start);
}

double get_avg(uint64_t *ptr, uint64_t n)
{
	uint64_t sum = 0;
	for (uint64_t i = n/10; i < n; i++)
		sum += ptr[i];
	return (((double)(sum)) / (n - n/10));
}

int main()
{
	uint32_t i, start, fn_index;
	uint64_t (*results)[num_runs] = calloc(num_runs * fnc, sizeof(uint64_t));

	srand(ns());
	for (uint64_t run = 0; run < num_runs; run++) 
	{
		start = rand();
		for (i = start; i < start + fnc; i++)
		{
			fn_index = i % fnc;
			results[fn_index][run] = benchmark_rng(fn_index);
		}
    }
	for (i = 0; i < fnc; i++)
		printf("Function %d: %f ns\n", i, printns(get_avg(results[i], num_runs)));
	printf("\n%f, %d, %lld", resf, resi, resl);
	free(results);
}
