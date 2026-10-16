#include "printf.h"

int	format_uhex(t_buf *buf, unsigned int n)
{
	char		s[12];
	int			len;
	int			res;

	len = buf_ultoa_base(s, (long long)n, "0123456789ABCDEF");
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

int	format_lhex(t_buf *buf, unsigned int n)
{
	char		s[12];
	int			len;
	int			res;

	len = buf_ultoa_base(s, (long long)n, "0123456789abcdef");
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
