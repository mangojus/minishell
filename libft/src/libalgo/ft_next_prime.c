#include "libalgo.h"

long	ft_next_prime(long nbr)
{
	while (ft_is_prime(nbr) == 0)
		nbr++;
	return (nbr);
}
