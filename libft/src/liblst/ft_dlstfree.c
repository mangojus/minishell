#include "liblst.h"

void	ft_dlstfree(t_dlst **lst)
{
	t_dlst	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free(*lst);
		(*lst) = next;
	}
}
