#include "env.h"

t_env	**env_dlstadd_front(t_env **lst, t_env *node)
{
	if (!lst || !node)
		return (NULL);
	node->prev = NULL;
	node->next = *lst;
	if (*lst)
		(*lst)->prev = node;
	*lst = node;
	return (lst);
}
