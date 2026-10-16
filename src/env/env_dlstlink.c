#include "env.h"

void	env_dlstlink(t_env *a, t_env *b)
{
	if (a)
		a->next = b;
	if (b)
		b->prev = a;
}
