#include "libalgo.h"

long	ft_fibonacci(size_t i)
{
	long	res;

	if (i == 0)
		return (0);
	if (i == 1)
		return (1);
	res = ft_fibonacci(i - 1) + ft_fibonacci(i - 2);
	return (res);
}
