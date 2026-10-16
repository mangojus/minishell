#include "libstr.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*dst;
	char	*tmp;

	if (!s1 && !s2 && !s3)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s2)
		return (ft_strjoin(s1, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	tmp = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!tmp)
		return (NULL);
	dst = tmp;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	while (*s3)
		*tmp++ = *s3++;
	*tmp = '\0';
	return (dst);
}
