#include "libstr.h"

static size_t	ft_count_nbr(int n, size_t div)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= div;
	}
	return (count);
}

char	*ft_itoa_base(int nbr, char *base)
{
	char	*dst;
	size_t	count;
	size_t	div;

	div = ft_strlen(base);
	if (nbr == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (nbr == 0)
		return (ft_strdup("0"));
	count = ft_count_nbr(nbr, div);
	dst = ft_calloc((count + 1), sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (nbr < 0)
	{
		nbr = -nbr;
		dst[0] = '-';
	}
	while (nbr > 0)
	{
		dst[--count] = base[nbr % div];
		nbr /= div;
	}
	return (dst);
}
