#include "libchar.h"

bool	ft_ischarset(int c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}
