#include "command.h"

void	cmd_dlstfree(t_cmd **lst)
{
	t_cmd	*it;
	t_cmd	*tmp;

	it = *lst;
	while (it)
	{
		tmp = it->next;
		if (it->args)
			ft_free_sptr(it->args);
		if (it->fds)
			tok_dlstfree(&it->fds);
		free(it);
		it = tmp;
	}
	*lst = NULL;
}
