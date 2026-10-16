#include "minishell.h"

static t_err	setup_first_child(t_fds *fds, t_cmd *cmd)
{
	t_err	status;

	status = ERR_OK;
	if (fds->infile != -1)
		status = dup2_redirect(fds->infile, STDIN_FILENO);
	if (fds->outfile != -1)
		status = dup2_redirect(fds->outfile, STDOUT_FILENO);
	else if (cmd->next)
		status = dup2_redirect(fds->pipe1[1], STDOUT_FILENO);
	return (status);
}

static t_err	setup_last_child(t_fds *fds, t_cmd *cmd)
{
	t_err	status;

	status = ERR_OK;
	if (fds->infile != -1)
		status = dup2_redirect(fds->infile, STDIN_FILENO);
	if (fds->outfile != -1)
		status = dup2_redirect(fds->outfile, STDOUT_FILENO);
	if (cmd->index % 2 == 0 && fds->infile == -1)
		status = dup2_redirect(fds->pipe2[0], STDIN_FILENO);
	if (cmd->index % 2 == 1 && fds->infile == -1)
		status = dup2_redirect(fds->pipe1[0], STDIN_FILENO);
	return (status);
}

static t_err	setup_middle_child(t_fds *fds, t_cmd *cmd)
{
	t_err	status;

	status = ERR_OK;
	if (fds->infile != -1)
		status = dup2_redirect(fds->infile, STDIN_FILENO);
	if (fds->outfile != -1)
		status = dup2_redirect(fds->outfile, STDOUT_FILENO);
	if (cmd->index % 2 == 0 && fds->infile == -1)
		status = dup2_redirect(fds->pipe2[0], STDIN_FILENO);
	if (cmd->index % 2 == 0 && fds->outfile == -1)
		status = dup2_redirect(fds->pipe1[1], STDOUT_FILENO);
	if (cmd->index % 2 == 1 && fds->infile == -1)
		status = dup2_redirect(fds->pipe1[0], STDIN_FILENO);
	if (cmd->index % 2 == 1 && fds->outfile == -1)
		status = dup2_redirect(fds->pipe2[1], STDOUT_FILENO);
	return (status);
}

static void	child_process(t_cmd *cmd, t_fds *fds, t_data *data)
{
	if (!manage_fds(cmd, fds))
	{
		close_fds(fds);
		free_all_data(data);
		exit(ERR_BASH);
	}
	child_signals();
	if (cmd->index == 0)
		data->status = setup_first_child(fds, cmd);
	else if (cmd->type == 1)
		data->status = setup_last_child(fds, cmd);
	else
		data->status = setup_middle_child(fds, cmd);
	close_fds(fds);
	if (data->status != ERR_OK)
	{
		free_all_data(data);
		exit(data->status);
	}
	execute_cmd(cmd->args, data);
}

int	child(t_cmd *cmd, t_fds *fds, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		close_fds(fds);
		free_all_data(data);
		return (-1);
	}
	if (pid == 0)
		child_process(cmd, fds, data);
	return (pid);
}
