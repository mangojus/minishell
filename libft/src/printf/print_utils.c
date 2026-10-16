#include "printf.h"

int	print_char(enum e_type type, va_list *args, int fd)
{
	size_t	len;
	char	c;
	char	*str;

	len = 0;
	if (type == CHAR_TYPE)
	{
		c = va_arg(*args, int);
		len = write(fd, &c, 1);
	}
	else if (type == STR_TYPE)
	{
		str = va_arg(*args, char *);
		if (str == NULL)
			return (len = write(fd, "(null)", 6));
		len = write(fd, str, ft_strlen(str));
	}
	return (len);
}

int	print_ptr(va_list *args, int fd)
{
	void	*ptr;
	char	*str;
	int		len;

	len = 0;
	ptr = va_arg(*args, void *);
	if (ptr == NULL)
		return (len = write(fd, "(nil)", 5));
	str = ft_ultoa_base((unsigned long)ptr, "0123456789abcdef");
	if (str == NULL)
		return (0);
	len += write(fd, "0x", 2);
	len += write(fd, str, ft_strlen(str));
	free(str);
	return (len);
}

int	print_num(enum e_type type, va_list *args, int fd)
{
	long long	nbr;
	char		*str;
	int			len;

	len = 0;
	if (type == INT_TYPE)
	{
		nbr = va_arg(*args, int);
		str = ft_itoa(nbr);
		len = write(fd, str, ft_strlen(str));
		free(str);
	}
	else if (type == UINT_TYPE)
	{
		nbr = va_arg(*args, unsigned int);
		str = ft_ultoa(nbr);
		len = write(fd, str, ft_strlen(str));
		free(str);
	}
	return (len);
}

int	print_hex(enum e_type type, va_list *args, int fd)
{
	long long	res;
	char		*str;
	int			len;

	len = 0;
	res = va_arg(*args, unsigned int);
	if (type == HEX_LOW_TYPE)
	{
		str = ft_ultoa_base(res, "0123456789abcdef");
		len = write(fd, str, ft_strlen(str));
		free(str);
	}
	else if (type == HEX_UPP_TYPE)
	{
		str = ft_ultoa_base(res, "0123456789ABCDEF");
		len = write(fd, str, ft_strlen(str));
		free(str);
	}
	return (len);
}
