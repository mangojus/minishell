#include "libstr.h"

static int	ft_count_nbr(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		count;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	count = ft_count_nbr(n);
	dst = ft_calloc((count + 1), sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		dst[0] = '-';
	}
	while (n > 0)
	{
		dst[--count] = (n % 10) + '0';
		n = n / 10;
	}
	return (dst);
}
