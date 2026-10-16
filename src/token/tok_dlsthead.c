#include "token.h"

t_tok	*tok_dlsthead(t_tok *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}
