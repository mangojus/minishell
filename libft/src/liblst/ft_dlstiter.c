#include "liblst.h"

void	ft_dlstiter(t_dlst *lst, void (*f)(int))
{
	t_dlst	*tmp;

	if (!lst || !f)
		return ;
	tmp = lst;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}
