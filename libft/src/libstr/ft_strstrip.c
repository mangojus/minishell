#include "libstr.h"

void	ft_strstrip(char *s, char *set)
{
	char	*tmp;

	tmp = s;
	while (*s)
	{
		if (!ft_strchr(set, *s))
		{
			*tmp = *s;
			tmp++;
		}
		s++;
	}
	*tmp = '\0';
}
