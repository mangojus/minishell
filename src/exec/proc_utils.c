#include "minishell.h"

static void	update_status(int pid, int last, int wst, int *status)
{
	int	sig;

	if (WIFSIGNALED(wst))
	{
		sig = WTERMSIG(wst);
		if (pid == last)
			*status = 128 + sig;
	}
	else if (pid == last && WIFEXITED(wst))
		*status = WEXITSTATUS(wst);
}

t_err	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
		return (ERR_SIGINT);
	return (ERR_OK);
}

int	wait_children(int nb_cmds, int last_pid)
{
	int	status;
	int	i;
	int	wst;
	int	pid;

	status = 0;
	i = 0;
	while (i < nb_cmds)
	{
		pid = wait(&wst);
		if (pid == -1)
		{
			if (errno == ECHILD)
				break ;
			perror("wait error");
			return (1);
		}
		update_status(pid, last_pid, wst, &status);
		i++;
	}
	return (status);
}
