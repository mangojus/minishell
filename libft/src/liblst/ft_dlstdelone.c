#include "liblst.h"

void	ft_dlstdelone(t_dlst *lst, void (*del)(int))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
