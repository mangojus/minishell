#include "token.h"

void	tok_dlstadd_back(t_tok **lst, t_tok *new)
{
	t_tok	*tmp;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*lst = new;
}
