#include "libstr.h"

char	*ft_strpbrk(const char *s, const char *set)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_ischarset(s[i], set))
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
