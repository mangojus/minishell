#include <libstr.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*dst;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s, len);
	dst[len] = '\0';
	return (dst);
}
