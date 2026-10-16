#include "minishell.h"

static int	refresh_rl_vars(void)
{
	return (0);
}

static void	read_write_heredoc(int fd, t_tok *tok, t_data *data)
{
	char	*line;
	char	*exp;

	while (true && !g_signo)
	{
		line = readline("> ");
		if (!line || g_signo)
			break ;
		if (!ft_strcmp(line, tok->content))
			break ;
		exp = expand_token(line, data, true);
		ft_nullfree((void **)&line);
		if (!exp)
		{
			close_fd(&fd);
			free_all_data(data);
			exit(EXIT_FAILURE);
		}
		ft_rprintf(fd, "%s\n", exp);
		free(exp);
	}
	free(line);
	close_fd(&fd);
	free_all_data(data);
}

static bool	fork_hdoc(t_tok *tok, t_fds *fds, pid_t *pid, t_data *data)
{
	*pid = fork();
	if (*pid == -1)
	{
		close_fds(fds);
		free_all_data(data);
		return (false);
	}
	if (*pid == 0)
	{
		close_fd(&fds->p[0]);
		rl_event_hook = &refresh_rl_vars;
		g_signo = 0;
		install_sigint_hd();
		read_write_heredoc(fds->p[1], tok, data);
		signal(SIGINT, sigint_heredoc);
		close_fd(&fds->p[1]);
		free_all_data(data);
		if (g_signo == 1)
			exit(130);
		exit(EXIT_SUCCESS);
	}
	return (true);
}

static bool	setup_heredoc(t_tok *tok, t_data *data)
{
	pid_t	pid;
	t_fds	fds;

	ft_memset(&fds, -1, sizeof(fds));
	if (pipe(fds.p) == -1)
		return (false);
	if (!fork_hdoc(tok, &fds, &pid, data))
		return (false);
	data->status = wait_child(pid);
	tok->fd = fds.p[0];
	close_fd(&fds.p[1]);
	if (data->status == 130)
		return (false);
	return (true);
}

bool	cancel_on_heredoc(t_data *data)
{
	t_cmd	*current;
	t_tok	*tok;

	current = data->cmd;
	while (current)
	{
		tok = current->fds;
		while (tok)
		{
			if (tok->type == HDOC && !setup_heredoc(tok, data))
			{
				data->status = ERR_SIGINT;
				restore_parent_signals();
				return (true);
			}
			tok = tok->next;
		}
		current = current->next;
	}
	return (false);
}
