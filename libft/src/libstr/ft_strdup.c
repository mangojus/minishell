#include "libstr.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s, len);
	dst[len] = '\0';
	return (dst);
}
