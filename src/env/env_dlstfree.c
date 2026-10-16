#include "env.h"

void	env_dlstfree(t_env **env)
{
	t_env	*it;
	t_env	*next;

	it = *env;
	while (it)
	{
		next = it->next;
		free(it->key);
		free(it->value);
		free(it);
		it = next;
	}
	*env = NULL;
}
