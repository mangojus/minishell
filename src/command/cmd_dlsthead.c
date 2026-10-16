#include "command.h"

t_cmd	*cmd_dlsthead(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}
