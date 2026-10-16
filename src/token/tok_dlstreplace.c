#include "token.h"

t_tok	*tok_dlstreplace(t_tok **lst, t_tok *old, t_tok *new)
{
	t_tok	*last;
	t_tok	*next;

	next = old->next;
	if (!new)
	{
		tok_dlstlink(old->prev, old->next);
		if (old == *lst)
			*lst = old->next;
		free(old->content);
		free(old);
		return (next);
	}
	last = tok_dlstlast(new);
	tok_dlstlink(old->prev, new);
	tok_dlstlink(last, next);
	if (old == *lst)
		*lst = new;
	free(old->content);
	free(old);
	return (next);
}
