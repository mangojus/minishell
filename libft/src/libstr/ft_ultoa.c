#include "libstr.h"

static int	ft_count_nbr(unsigned long n)
{
	size_t	count;

	count = 0;
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_ultoa(unsigned long n)
{
	char	*dst;
	int		count;

	if (n == 0)
		return (ft_strdup("0"));
	count = ft_count_nbr(n);
	dst = ft_calloc((count + 1), sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (n > 0)
	{
		dst[--count] = (n % 10) + '0';
		n = n / 10;
	}
	return (dst);
}
