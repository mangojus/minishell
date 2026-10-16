#include "libstr.h"

char	*ft_strquote(const char *s)
{
	char	*dst;
	size_t	len;

	if (!s)
		return (ft_strdup(""));
	len = ft_strlen(s);
	dst = malloc(len + 3);
	if (!dst)
		return (NULL);
	dst[0] = '"';
	ft_memcpy(dst + 1, s, len);
	dst[len + 1] = '"';
	dst[len + 2] = '\0';
	return (dst);
}
