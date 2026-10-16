#include "libfd.h"

void	ft_close_fd(int *fd)
{
	if (*fd >= 3)
	{
		close(*fd);
		*fd = -1;
	}
}
