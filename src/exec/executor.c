#include "minishell.h"

static void	close_all_heredocs(t_cmd *cmd)
{
	t_cmd	*c;
	t_tok	*t;

	c = cmd;
	while (c)
	{
		t = c->fds;
		while (t)
		{
			if (t->type == HDOC && t->fd != -1)
				close_fd(&t->fd);
			t = t->next;
		}
		c = c->next;
	}
}

static int	run_cmds(t_cmd **cmd, t_fds *fds, t_data *data)
{
	t_cmd	*current;
	int		last_pid;
	int		count;
	int		status;

	last_pid = -1;
	count = 0;
	current = *cmd;
	while (current)
	{
		if (open_next_pipe(current, count, fds, data))
			return (1);
		last_pid = child(current, fds, data);
		if (last_pid == -1)
			return (-1);
		close_previous_pipe_parent(current, fds);
		count++;
		current = current->next;
	}
	close_fds(fds);
	status = wait_children(count, last_pid);
	close_all_heredocs(*cmd);
	return (status);
}

void	exec_line(t_data *data)
{
	t_fds	fds;
	t_cmd	*cmd;

	ignore_parent_signals();
	if (cancel_on_heredoc(data))
	{
		restore_parent_signals();
		return ;
	}
	ft_memset(&fds, -1, sizeof(fds));
	cmd = data->cmd;
	if ((cmd->next == NULL) && (is_builtin(cmd->args[0])))
		data->status = handle_single_builtin(cmd, &fds, data);
	else
		data->status = run_cmds(&data->cmd, &fds, data);
	if (data->status == ERR_MALLOC)
		error_exit("exec", data);
	if (data->status == 131)
		ft_rprintf(2, "Quit (core dumped)\n");
	cmd_dlstfree(&data->cmd);
	restore_parent_signals();
}
