#include "printf.h"

int	flush_buffer(t_buf *buf)
{
	char	*ptr;
	int		len;
	int		res;

	if (buf->len == 0)
		return (0);
	ptr = ft_memchr(buf->arr, '\n', buf->len);
	if (ptr)
		len = ptr - buf->arr + 1;
	else
		len = buf->len;
	res = write(buf->fd, buf->arr, len);
	if (res == -1)
		return (-1);
	if (res < buf->len)
		ft_memmove(buf->arr, buf->arr + res, buf->len - res);
	buf->len -= res;
	return (res);
}

static int	parsing_format(t_buf *buf, const char *format, va_list *args)
{
	if (*format == 'c')
		return (format_char(buf, va_arg(*args, int)));
	else if (*format == 's')
		return (format_str(buf, va_arg(*args, char *)));
	else if (*format == 'p')
		return (format_ptr(buf, va_arg(*args, void *)));
	else if (*format == 'd' || *format == 'i')
		return (format_int(buf, va_arg(*args, int)));
	else if (*format == 'u')
		return (format_uint(buf, va_arg(*args, unsigned int)));
	else if (*format == 'x')
		return (format_lhex(buf, va_arg(*args, unsigned int)));
	else if (*format == 'X')
		return (format_uhex(buf, va_arg(*args, unsigned int)));
	else if (*format == '%')
		return (format_char(buf, '%'));
	return (-1);
}

int	ft_rprintf(int fd, const char *format, ...)
{
	static t_buf	buf = {.size = BUF_SIZE, .len = 0, .fd = -1};
	va_list			args;
	int				res;
	int				len;

	if (!format)
		return (-1);
	va_start(args, format);
	buf.fd = fd;
	len = 0;
	while (*format)
	{
		if (*format == '%')
			res = parsing_format(&buf, ++format, &args);
		else
			res = format_char(&buf, *format);
		if (res == -1)
			break ;
		len += res;
		format++;
	}
	va_end(args);
	if (flush_buffer(&buf) == -1 || res == -1)
		return (-1);
	return (len);
}
