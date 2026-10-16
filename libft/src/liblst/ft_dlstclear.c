#include "liblst.h"

void	ft_dlstclear(t_dlst **lst, void (*del)(int))
{
	t_dlst	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_dlstdelone(*lst, del);
		*lst = tmp;
	}
}
