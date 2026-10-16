#include "libstr.h"

int	ft_stridx(const char *s, const char *set)
{
	int	i;

	i = 0;
	while (s[i] || (ft_ischarset('\0', set) && s[i] == '\0'))
	{
		if (ft_ischarset(s[i], set))
			return (i);
		i++;
	}
	return (-1);
}
