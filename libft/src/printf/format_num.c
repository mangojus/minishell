#include "printf.h"

int	format_int(t_buf *buf, int n)
{
	char		s[12];
	int			len;
	int			res;

	len = buf_itoa(s, n);
	if (buf->len + len >= buf->size)
	{
		res = flush_buffer(buf);
		if (res == -1)
			return (-1);
	}
	ft_memcpy(buf->arr + buf->len, s, len);
	buf->len += len;
	return (len);
}

int	format_uint(t_buf *buf, unsigned int n)
{
	char		s[12];
	int			len;
	int			res;

	len = buf_ultoa_base(s, n, "0123456789");
	if (buf->len + len >= buf->size)
	{
		res = flush_buffer(buf);
		if (res == -1)
			return (-1);
	}
	ft_memcpy(buf->arr + buf->len, s, len);
	buf->len += len;
	return (len);
}
