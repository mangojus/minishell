#include "printf.h"

int	format_ptr(t_buf *buf, void *ptr)
{
	char	s[19];
	int		len;
	int		res;

	if (!ptr)
		ft_strlcpy(s, "(nil)", sizeof(s));
	else
	{
		buf_ultoa_base(s + 2, (unsigned long)ptr, "0123456789abcdef");
		s[0] = '0';
		s[1] = 'x';
	}
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
