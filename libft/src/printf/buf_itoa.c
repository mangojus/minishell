#include "printf.h"

static int	count_nbr(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	buf_itoa(char *buf, int n)
{
	int	len;
	int	i;

	if (n == INT_MIN)
	{
		ft_strlcpy(buf, "-2147483648", 12);
		return (11);
	}
	len = count_nbr(n);
	i = len - 1;
	buf[len] = '\0';
	if (n == 0)
		buf[0] = '0';
	else if (n < 0)
	{
		buf[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		buf[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (len);
}
