#include "token.h"

void	tok_dlstiter(t_tok *lst, void (*f)(t_tok *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}
