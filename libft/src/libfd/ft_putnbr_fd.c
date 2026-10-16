#include "libfd.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	res;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	res = (n % 10) + '0';
	ft_putchar_fd(res, fd);
}
