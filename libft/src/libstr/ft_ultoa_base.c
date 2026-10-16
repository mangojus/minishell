#include "libstr.h"

static size_t	ft_count_nbr(unsigned long n, size_t div)
{
	size_t	count;

	count = 0;
	while (n > 0)
	{
		count++;
		n /= div;
	}
	return (count);
}

char	*ft_ultoa_base(unsigned long nbr, char *base)
{
	char	*dst;
	size_t	count;
	size_t	div;

	div = ft_strlen(base);
	if (nbr == 0)
		return (ft_strdup("0"));
	count = ft_count_nbr(nbr, div);
	dst = ft_calloc((count + 1), sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (nbr > 0)
	{
		dst[--count] = base[nbr % div];
		nbr /= div;
	}
	return (dst);
}
