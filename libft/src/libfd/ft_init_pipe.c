#include "libfd.h"

bool	ft_init_pipe(t_pipe *p)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (false);
	p->r = fd[0];
	p->w = fd[1];
	return (true);
}
