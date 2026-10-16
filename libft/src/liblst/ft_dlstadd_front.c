#include "liblst.h"

void	ft_dlstadd_front(t_dlst **lst, t_dlst *new)
{
	if (lst)
	{
		new->next = *lst;
		(*lst)->prev = new;
		*lst = new;
	}
	else if (!lst)
		*lst = new;
}
