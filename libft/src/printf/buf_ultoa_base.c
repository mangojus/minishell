#include "printf.h"

static int	count_nbr(unsigned long n, int div)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n /= div;
	}
	return (count);
}

int	buf_ultoa_base(char *buf, unsigned long n, char *base)
{
	int	div;
	int	len;
	int	i;

	div = ft_strlen(base);
	len = count_nbr(n, div);
	i = len - 1;
	buf[len] = '\0';
	if (n == 0)
	{
		buf[0] = '0';
		return (1);
	}
	while (n > 0)
	{
		buf[i--] = base[n % div];
		n /= div;
	}
	return (len);
}
