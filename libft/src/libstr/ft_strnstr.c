#include "libstr.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	keep;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *)big);
	while (big[i])
	{
		keep = i;
		while ((big[i] == little[j]) && i < len && little[j])
		{
			i++;
			j++;
		}
		if (little[j] == 0)
			return ((char *)&big[keep]);
		i = keep;
		j = 0;
		i++;
	}
	return (NULL);
}
