#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "env"))
		return (true);
	else if (!ft_strcmp(cmd, "echo"))
		return (true);
	else if (!ft_strcmp(cmd, "exit"))
		return (true);
	else if (!ft_strcmp(cmd, "export"))
		return (true);
	else if (!ft_strcmp(cmd, "unset"))
		return (true);
	else if (!ft_strcmp(cmd, "cd"))
		return (true);
	else if (!ft_strcmp(cmd, "pwd"))
		return (true);
	return (false);
}

t_err	exec_builtin(char **args, t_data *data)
{
	t_err	status;

	status = ERR_OK;
	if (!ft_strcmp(args[0], "env"))
		status = ft_env(args, &data->env);
	else if (!ft_strcmp(args[0], "echo"))
		status = ft_echo(args);
	else if (!ft_strcmp(args[0], "exit"))
		status = ft_exit(args, data);
	else if (!ft_strcmp(args[0], "export"))
		status = ft_export(args, &data->env);
	else if (!ft_strcmp(args[0], "unset"))
		status = ft_unset(args, &data->env);
	else if (!ft_strcmp(args[0], "cd"))
		status = ft_cd(args, &data->env);
	else if (!ft_strcmp(args[0], "pwd"))
		status = ft_pwd();
	return (status);
}

static void	redirect_fd(int newfd, int stdfd, int *save)
{
	if (newfd == -1)
		return ;
	*save = dup(stdfd);
	dup2_redirect(newfd, stdfd);
}

static void	restore_fd(int save, int stdfd)
{
	if (save == -1)
		return ;
	dup2_redirect(save, stdfd);
	close_fd(&save);
}

int	handle_single_builtin(t_cmd *cmd, t_fds *fds, t_data *data)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = -1;
	save_stdout = -1;
	if (!cmd || cmd->next != NULL || !is_builtin(cmd->args[0]))
		return (0);
	if (!manage_fds(cmd, fds))
	{
		data->last_status = 1;
		close_fds(fds);
		return (1);
	}
	redirect_fd(fds->infile, STDIN_FILENO, &save_stdin);
	redirect_fd(fds->outfile, STDOUT_FILENO, &save_stdout);
	data->last_status = exec_builtin(cmd->args, data);
	restore_fd(save_stdin, STDIN_FILENO);
	restore_fd(save_stdout, STDOUT_FILENO);
	close_fds(fds);
	return (data->last_status);
}
