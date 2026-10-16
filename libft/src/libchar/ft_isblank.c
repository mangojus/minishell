#include "libchar.h"

bool	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
