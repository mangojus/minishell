#include "libstr.h"

char	*ft_strtok(char *s, const char *set, char **endptr)
{
	char	*token;
	char	*end;

	if (s)
		*endptr = s;
	if (*endptr == NULL)
		return (NULL);
	*endptr += ft_strspn(*endptr, set);
	if (**endptr == '\0')
		return (NULL);
	end = ft_strpbrk(*endptr, set);
	token = *endptr;
	if (end)
	{
		*end = '\0';
		*endptr = end + 1;
	}
	else
		*endptr = NULL;
	return (token);
}
