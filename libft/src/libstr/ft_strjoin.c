#include "libstr.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	char	*tmp;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	tmp = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tmp)
		return (NULL);
	dst = tmp;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (dst);
}
