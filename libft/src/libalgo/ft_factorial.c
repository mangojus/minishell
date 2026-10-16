#include "libalgo.h"

long	ft_factorial(long nbr)
{
	long	res;
	long	x;

	res = 1;
	x = 1;
	if (nbr < 0)
		return (0);
	if (nbr == 0)
		return (1);
	while (x <= nbr)
	{
		res *= x;
		x++;
	}
	return (res);
}
