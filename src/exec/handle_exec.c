#include "minishell.h"

static t_err	search_cmd(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (set_err_to_errno());
	if (S_ISDIR(sb.st_mode))
		return (ERR_ISDIR);
	if (access(path, X_OK) == -1)
		return (ERR_ACCESS);
	return (ERR_OK);
}

static t_err	find_path(char **path, const char *arg, char *buf)
{
	char	*it;
	char	*endptr;

	endptr = NULL;
	it = ft_strtok(buf, ":", &endptr);
	while (it)
	{
		*path = ft_strjoin3(it, "/", arg);
		if (!*path)
			return (ERR_MALLOC);
		if (search_cmd(*path) == ERR_OK)
			return (ERR_OK);
		ft_nullfree((void **)path);
		it = ft_strtok(NULL, ":", &endptr);
	}
	return (ERR_NOTFOUND);
}

static t_err	get_path(char **path, const char *arg, char **envp)
{
	t_err	status;
	char	*value;
	char	*buf;

	value = get_env_value(envp, "PATH");
	if (ft_strchr(arg, '/') || !value || !*value)
	{
		*path = ft_strdup(arg);
		if (!*path)
			return (ERR_MALLOC);
		status = search_cmd(*path);
	}
	else
	{
		buf = ft_strdup(value);
		if (!buf)
			return (ERR_MALLOC);
		status = find_path(path, arg, buf);
		free(buf);
	}
	return (status);
}

static void	launch_execve(char **args, t_data *data)
{
	char	**envp;
	char	*path;

	envp = env_dlstconvert(data->env);
	if (!envp)
	{
		data->status = ERR_MALLOC;
		error_exit("exec", data);
	}
	path = NULL;
	data->status = get_path(&path, args[0], envp);
	if (data->status != ERR_OK)
	{
		free(path);
		ft_free_sptr(envp);
		error_exit(args[0], data);
	}
	execve(path, args, envp);
	data->status = set_err_to_errno();
	free(path);
	ft_free_sptr(envp);
	free_all_data(data);
	error_exit(args[0], data);
}

void	execute_cmd(char **args, t_data *data)
{
	if (!args || !args[0])
	{
		free_all_data(data);
		exit(EXIT_SUCCESS);
	}
	else if (is_builtin(args[0]))
	{
		data->status = exec_builtin(args, data);
		free_all_data(data);
		exit(data->status);
	}
	else
		launch_execve(args, data);
}
