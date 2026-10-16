#include "token.h"

void	tok_dlstsplit(t_tok *a, t_tok *b)
{
	if (!a || !b)
		return ;
	if (a == b->prev)
	{
		a->next = NULL;
		b->prev = NULL;
	}
	else if (a == b->next)
	{
		a->prev = NULL;
		b->next = NULL;
	}
}
