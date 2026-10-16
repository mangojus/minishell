#include "token.h"

void	tok_dlstlink(t_tok *a, t_tok *b)
{
	if (a)
		a->next = b;
	if (b)
		b->prev = a;
}
