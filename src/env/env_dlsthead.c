#include "env.h"

t_env	*env_dlsthead(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}
