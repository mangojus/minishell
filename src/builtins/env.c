#include "minishell.h"

t_err	ft_env(char **args, t_env **env)
{
	t_env	*var;

	if (args && args[1])
	{
		ft_rprintf(2, "msh: env: too many arguments\n");
		return (ERR_BASH);
	}
	var = *env;
	while (var)
	{
		if (var->value)
			ft_rprintf(1, "%s=%s\n", var->key, var->value);
		var = var->next;
	}
	return (ERR_OK);
}
