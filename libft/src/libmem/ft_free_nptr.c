#include "libmem.h"

void	ft_free_nptr(int **num, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(num[i]);
		i++;
	}
	free(num);
}
