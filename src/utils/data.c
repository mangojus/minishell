#include "minishell.h"

volatile sig_atomic_t	g_signo = 0;

void	free_all_data(t_data *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->tok)
		tok_dlstfree(&data->tok);
	if (data->cmd)
		cmd_dlstfree(&data->cmd);
	if (data->env)
		env_dlstfree(&data->env);
	if (data->cwd)
	{
		free(data->cwd);
		data->cwd = NULL;
	}
}

void	free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->tok)
		tok_dlstfree(&data->tok);
	data->tok = NULL;
	if (data->cmd)
		cmd_dlstfree(&data->cmd);
	data->cmd = NULL;
}

static bool	init_env(t_data *data, char **envp)
{
	t_env	*var;
	int		value;

	if (!*envp)
	{
		if (!env_dlstadd_back(&data->env, env_dlstnew("PWD", data->cwd)) \
			|| !env_dlstadd_back(&data->env, env_dlstnew("OLDPWD", NULL)) \
			|| !env_dlstadd_back(&data->env, env_dlstnew("SHLVL", "1")))
			return (false);
		return (true);
	}
	if (!create_env_list(envp, &data->env))
		return (false);
	var = env_dlstfind(data->env, "SHLVL");
	if (var)
	{
		value = ft_atoi(var->value) + 1;
		free(var->value);
		var->value = ft_itoa(value);
		if (!var->value)
			return (false);
	}
	else if (!env_dlstadd_front(&data->env, env_dlstnew("SHLVL", "1")))
		return (false);
	return (true);
}

bool	init_data(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_bzero(data, sizeof(t_data));
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return (false);
	if (!init_env(data, envp))
		return (false);
	return (true);
}
