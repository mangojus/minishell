#include "minishell.h"

t_err	dup2_redirect(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		return (set_err_to_errno());
	}
	return (ERR_OK);
}

void	close_fds(t_fds *fds)
{
	close_fd(&fds->pipe1[0]);
	close_fd(&fds->pipe1[1]);
	close_fd(&fds->pipe2[0]);
	close_fd(&fds->pipe2[1]);
	close_fd(&fds->infile);
	close_fd(&fds->outfile);
	close_fd(&fds->p[0]);
	close_fd(&fds->p[1]);
}

void	close_fd(int *fd)
{
	if (!fd || *fd == -1)
		return ;
	if (*fd > 2)
		close(*fd);
	*fd = -1;
}
