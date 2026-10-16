#include "libalgo.h"

long	ft_iterative_power(long nbr, long pow)
{
	long	tmp;

	tmp = nbr;
	if (pow == 0)
		return (1);
	if (pow < 0)
		return (0);
	while (pow > 1)
	{
		nbr *= tmp;
		pow--;
	}
	return (nbr);
}
