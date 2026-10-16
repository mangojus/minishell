#include "minishell.h"

static void	update_old_pwd(t_env *env, char *oldpwd)
{
	t_env	*var;

	var = env_dlstfind(env, "OLDPWD");
	if (var)
	{
		free(var->value);
		var->value = oldpwd;
	}
	else
		free(oldpwd);
}

static t_err	update_pwd(t_env *env, char *oldpwd)
{
	t_env	*var;
	char	*newpwd;

	var = env_dlstfind(env, "PWD");
	if (!var)
	{
		free(oldpwd);
		return (ERR_OK);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		if (errno == ENOMEM)
			return (ERR_MALLOC);
		ft_rprintf(2, "chdir: error retrieving current directory: ");
		ft_rprintf(2, "getcwd: cannot access parent directories: ");
		ft_rprintf(2, "%s\n", strerror(errno));
		return (ERR_BASH);
	}
	free(var->value);
	var->value = newpwd;
	update_old_pwd(env, oldpwd);
	return (ERR_OK);
}

static char	*get_path(char **args, t_env *env)
{
	t_env	*var;
	char	*path;

	path = args[1];
	if (!path)
	{
		var = env_dlstfind(env, "HOME");
		if (!var)
		{
			ft_rprintf(2, "msh: cd: HOME not set\n");
			return (NULL);
		}
		path = var->value;
	}
	else if (!ft_strcmp(path, "~"))
		path = getenv("HOME");
	return (path);
}

t_err	ft_cd(char **args, t_env **env)
{
	char	*oldpwd;
	char	*path;

	if (args[1] && args[2])
	{
		ft_rprintf(2, "msh: cd: too many arguments\n");
		return (ERR_BASH);
	}
	path = get_path(args, *env);
	if (!path)
		return (ERR_BASH);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		if (errno == ENOMEM)
			return (ERR_MALLOC);
	}
	if (chdir(path) == -1)
	{
		free(oldpwd);
		ft_rprintf(2, "msh: cd: %s: %s\n", path, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (update_pwd(*env, oldpwd));
}
