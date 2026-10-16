#include "get_next_line.h"

void	gnl_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

int	gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] || ((unsigned char)c == 0 && s[i] == 0))
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}

void	*gnl_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
		((unsigned char *)dest)[i] = 0;
	}
	else
	{
		((unsigned char *)dest)[n] = 0;
		while (n-- > 0)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	}
	return ((unsigned char *)dest);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (gnl_strchr(s2, '\n') != -1)
		len = gnl_strchr(s2, '\n') + 1;
	else
		len = gnl_strlen(s2);
	dst = malloc((gnl_strlen(s1) + len + 1) * sizeof(char));
	if (dst == NULL)
		return (free((char *)s1), dst);
	while (s1 != NULL && s1[j])
		dst[i++] = s1[j++];
	j = 0;
	while (s2[j] && s2[j] != '\n')
		dst[i++] = s2[j++];
	if (s2[j] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (free((char *)s1), dst);
}
