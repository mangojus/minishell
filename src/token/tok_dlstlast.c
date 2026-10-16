#include "token.h"

t_tok	*tok_dlstlast(t_tok *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
