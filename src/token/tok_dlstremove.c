#include "token.h"

void	tok_dlstremove(t_tok **lst)
{
	t_tok	*node;
	t_tok	*tmp;

	if (!lst || !*lst)
		return ;
	node = *lst;
	if (node->next)
		tmp = node->next;
	else
		tmp = node->prev;
	tok_dlstlink(node->prev, node->next);
	free(node->content);
	free(node);
	*lst = tmp;
}
