#include <stdint.h>
#include <string.h>

float	Q_rsqrt(void *faddr_void)
{
	const float x2 = *((float *) faddr_void) * 0.5f;
	uint32_t *faddr = (uint32_t *) faddr_void;
	float y;

	*faddr  = (0x5f3759df - ((*faddr) >> 1));
	y = *((float *) faddr);
	y = y * (1.5f - (x2 * y * y));
	return(y);
}

float	ft_qinvsqrt2(void *ptr)
{
	t_32	*result = (t_32 *) ptr;

	const float x2 = (*result).f * 0.5;
	(*result).ui  = 0x5f3759df - ((*result).ui >> 1);
	(*result).f  = (*result).f * (1.5f - (x2 * (*result).f * (*result).f));
}

t_32	ft_qinvsqrt(t_32 number)
{
	const float	x = number.f * 0.5f;

	number.ui  = 0x5f3759df - ( number.ui >> 1 );
	number.f  = number.f * (1.5f - ( x * number.f * number.f ));
	return (number);
}

float	Q_rsqrt(void *faddr_void)
{
	const float x2 = *((float *) faddr_void) * 0.5f;
	uint32_t *faddr = (uint32_t *) faddr_void;
	float y;

	*faddr  = (0x5f3759df - ((*faddr) >> 1));
	y = *((float *) faddr);
	y = y * (1.5f - (x2 * y * y));
	return(y);
}


#include <stdio.h>
int	main(void)
{
	float x = 9.0f;
	printf("%f", Q_rsqrt(&x));
}