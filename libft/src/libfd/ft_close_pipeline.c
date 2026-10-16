#include "libfd.h"

void	ft_close_pipeline(t_pipe *pipeline, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
		ft_close_pipe(&pipeline[i++]);
}
