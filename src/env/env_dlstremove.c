#include "env.h"

t_env	*env_dlstremove(t_env **env)
{
	t_env	*node;
	t_env	*it;

	if (!env || !*env)
		return (NULL);
	node = *env;
	if (node->next)
		it = node->next;
	else
		it = node->prev;
	env_dlstlink(node->prev, node->next);
	free(node->key);
	free(node->value);
	free(node);
	*env = NULL;
	return (it);
}
