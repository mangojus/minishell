#include "libstr.h"

size_t	ft_strspn(const char *s, const char *set)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_ischarset(s[i], set))
			i++;
		else
			break ;
	}
	return (i);
}
