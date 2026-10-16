#include "libfd.h"

int	ft_pclose(t_file *stream)
{
	int	status;

	ft_close_fd(&stream->fd);
	status = 0;
	if (waitpid(stream->pid, &status, 0) == -1)
	{
		free(stream);
		return (-1);
	}
	free(stream);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
