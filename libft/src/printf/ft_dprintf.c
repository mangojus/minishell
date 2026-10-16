#include "printf.h"

static int	parsing_format(int len, const char *format, va_list *args, int fd)
{
	int	check_err;

	check_err = len;
	if (*format == 'c')
		len += print_char(CHAR_TYPE, args, fd);
	else if (*format == 's')
		len += print_char(STR_TYPE, args, fd);
	else if (*format == 'p')
		len += print_ptr(args, fd);
	else if (*format == 'd' || *format == 'i')
		len += print_num(INT_TYPE, args, fd);
	else if (*format == 'u')
		len += print_num(UINT_TYPE, args, fd);
	else if (*format == 'x')
		len += print_hex(HEX_LOW_TYPE, args, fd);
	else if (*format == 'X')
		len += print_hex(HEX_UPP_TYPE, args, fd);
	else if (*format == '%')
		len += write(fd, "%", 1);
	else
		return (-1);
	if (len < check_err)
		return (-1);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	if (!format)
		return (-1);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			len = parsing_format(len, ++format, &args, fd);
			if (len == -1)
				return (-1);
		}
		else
			len += write(fd, &format[0], 1);
		format++;
	}
	va_end(args);
	return (len);
}
