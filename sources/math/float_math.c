#include "core.hpp"

// Original doom algorithm
f32	qinvsqrt(f32 number) {
	u32 uNum = 0x5f3759df - (BITCAST(u32, number) >> 1);
	f32 fNum = BITCAST(float, uNum);
	fNum = fNum * (1.5f - (number * 0.5f * fNum * fNum));
	return (fNum);
}

// Modified doom algorithm
f32 inv_sqrt(f32 number) {
	u32 uNum = 0x5F1FFFF9ul - (BITCAST(u32, number) >> 1);
	f32 fNum = BITCAST(f32, uNum);

	return 0.703952253f * fNum * (2.38924456f - number * fNum * fNum);
}

// Check length division
float ft_average(float *array, size_t length) {
	float	sum;
	size_t	i;

	sum = 0;
	i = 0;
	while (i < length)
	{
		sum += *array;
		array++;
		i++;
	}
	return (sum / (float) length);
}
