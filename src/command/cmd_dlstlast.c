#include "command.h"

t_cmd	*cmd_dlstlast(t_cmd *lst)
{
	t_cmd	*it;

	if (!lst)
		return (NULL);
	it = lst;
	while (it->next)
		it = it->next;
	return (it);
}
