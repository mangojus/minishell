#include "liblst.h"

int	ft_dlstsize(t_dlst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
