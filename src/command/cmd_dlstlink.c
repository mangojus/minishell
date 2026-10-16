#include "command.h"

void	cmd_dlstlink(t_cmd *a, t_cmd *b)
{
	if (a)
		a->next = b;
	if (b)
		b->prev = a;
}
