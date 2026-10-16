#include "libmem.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	if (!dest || !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	}
	return ((void *)dest);
}
