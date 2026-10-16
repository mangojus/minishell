#include "liblst.h"

t_dlst	*ft_dlsthead(t_dlst *lst)
{
	t_dlst	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}
