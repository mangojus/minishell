#include "libfd.h"

void	ft_close_pipe(t_pipe *p)
{
	ft_close_fd(&p->r);
	ft_close_fd(&p->w);
}
