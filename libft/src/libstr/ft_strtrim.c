#include "libstr.h"

char	*ft_strtrim(char const *s, char const *set)
{
	char	*dst;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s || !set)
		return (NULL);
	start = ft_strspn(s, set);
	end = ft_strlen(s);
	while (end > start && ft_ischarset(s[end - 1], set))
		end--;
	len = end - start;
	if (len == 0)
		return (ft_strdup(""));
	dst = malloc((len + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s + start, len);
	dst[len] = '\0';
	return (dst);
}
