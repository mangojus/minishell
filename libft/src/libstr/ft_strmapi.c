#include "libstr.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;

	dst = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
