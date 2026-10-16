#include "env.h"

t_env	**env_dlstadd_back(t_env **lst, t_env *node)
{
	t_env	*last;

	if (!lst || !node)
		return (NULL);
	if (*lst)
	{
		last = env_dlstlast(*lst);
		last->next = node;
		node->prev = last;
	}
	else
		*lst = node;
	return (lst);
}
