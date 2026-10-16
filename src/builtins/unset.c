#include "minishell.h"

t_err	ft_unset(char **args, t_env **env)
{
	t_env	*var;
	int		i;

	if (!args[1])
		return (ERR_OK);
	i = 0;
	while (args[++i])
	{
		if (args[i][0] == '-')
		{
			ft_rprintf(2, "msh: unset: %s: invalid option\n", args[i]);
			ft_rprintf(2, "unset: usage: unset [name ...]\n");
			return (ERR_SYNTAX);
		}
		var = env_dlstfind(*env, args[i]);
		if (!var)
			continue ;
		else
		{
			*env = env_dlstremove(&var);
			*env = env_dlsthead(*env);
		}
	}
	return (ERR_OK);
}
