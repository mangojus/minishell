#include "printf.h"

int	format_char(t_buf *buf, int c)
{
	int	res;

	if (buf->len + 1 >= buf->size)
	{
		res = flush_buffer(buf);
		if (res == -1)
			return (-1);
	}
	buf->arr[buf->len] = c;
	buf->len += 1;
	return (1);
}

int	format_str(t_buf *buf, char *s)
{
	int	len;
	int	res;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
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
