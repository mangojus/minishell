#include "libstr.h"

size_t	ft_strtokcnt(const char *s, const char *set)
{
	size_t	in_tok;
	size_t	count;
	size_t	i;

	in_tok = 0;
	count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!ft_ischarset(s[i], set) && in_tok == 0)
		{
			in_tok = 1;
			count++;
		}
		else if (ft_ischarset(s[i], set))
			in_tok = 0;
		i++;
	}
	return (count);
}
