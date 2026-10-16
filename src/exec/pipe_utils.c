#include "minishell.h"

int	checked_pipe(int p[2], t_fds *fds, t_data *data)
{
	if (pipe(p) == -1)
	{
		perror("pipe");
		if (fds)
			close_fds(fds);
		if (data)
		{
			cmd_dlstfree(&data->cmd);
			data->last_status = 1;
		}
		return (-1);
	}
	return (0);
}

void	close_previous_pipe_parent(t_cmd *cmd, t_fds *fds)
{
	int	prev_type;
	int	*prevfds;

	if (cmd->index == 0)
		return ;
	prev_type = get_pipe(cmd->index - 1);
	if (prev_type == 1)
		prevfds = fds->pipe1;
	else
		prevfds = fds->pipe2;
	close_fd(&prevfds[0]);
	close_fd(&prevfds[1]);
}

int	open_next_pipe(t_cmd *cmd, int count, t_fds *fds, t_data *data)
{
	int	*fds_to_open;
	int	result;

	fds_to_open = NULL;
	result = 0;
	if (cmd->type != PIPE)
		return (0);
	if (count % 2 == 0)
		fds_to_open = fds->pipe1;
	else
		fds_to_open = fds->pipe2;
	result = checked_pipe(fds_to_open, fds, data);
	return (result);
}

int	get_pipe(size_t cmd_index)
{
	if (cmd_index % 2 == 0)
		return (1);
	return (2);
}
