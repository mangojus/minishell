#include "liblst.h"

void	ft_dlstadd_back(t_dlst **lst, t_dlst *new)
{
	t_dlst	*last;

	if (*lst)
	{
		last = ft_dlstlast(*lst);
		last->next = new;
		new->prev = last;
	}
	else if (!*lst)
		*lst = new;
}
