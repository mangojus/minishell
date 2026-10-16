#include "libalgo.h"

long	ft_is_prime(long nbr)
{
	long	x;

	x = 1;
	if (nbr <= 1)
		return (0);
	if (nbr == 2 || nbr == 3 || nbr == 5)
		return (1);
	while (x < nbr)
	{
		if (nbr == x * 2 || nbr == x * 3 || nbr == x * 5)
			return (0);
		x++;
	}
	return (1);
}
