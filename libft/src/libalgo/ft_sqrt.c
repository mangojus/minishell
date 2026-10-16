#include "libalgo.h"

long	ft_sqrt(long nbr)
{
	long	x;

	x = 0;
	if (nbr == 1)
		return (1);
	while (nbr != x * x && x < nbr / 2)
		x++;
	if (nbr == x * x)
		return (x);
	return (0);
}
