#include "liblst.h"

void	ft_dlstlink(t_dlst *l1, t_dlst *l2)
{
	if (l1->next)
		(l1->next)->prev = NULL;
	if (l2->prev)
		(l2->prev)->next = NULL;
	l1->next = l2;
	l2->prev = l1;
}
