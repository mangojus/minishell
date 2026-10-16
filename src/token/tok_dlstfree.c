#include "token.h"

void	tok_dlstfree(t_tok **lst)
{
	t_tok	*it;
	t_tok	*tmp;

	it = *lst;
	while (it)
	{
		tmp = it->next;
		free(it->content);
		free(it);
		it = tmp;
	}
	*lst = NULL;
}
