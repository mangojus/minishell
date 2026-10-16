#include "libchar.h"

bool	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (true);
	return (false);
}
