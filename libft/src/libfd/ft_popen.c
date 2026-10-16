#include "libfd.h"

static void	child_exec(char *cmd, char type, t_pipe *p)
{
	if (type == 'r')
	{
		if (dup2(p->w, STDOUT_FILENO) == -1)
		{
			ft_close_pipe(p);
			exit(EXIT_FAILURE);
		}
	}
	else if (type == 'w')
	{
		if (dup2(p->r, STDIN_FILENO) == -1)
		{
			ft_close_pipe(p);
			exit(EXIT_FAILURE);
		}
	}
	ft_close_pipe(p);
	execl("/bin/sh", "sh", "-c", cmd, NULL);
	exit(EXIT_FAILURE);
}

static t_file	*init_stream(t_pipe *p, pid_t pid, char type)
{
	t_file	*stream;

	stream = ft_calloc(1, sizeof(t_file));
	if (!stream)
	{
		ft_close_pipe(p);
		return (NULL);
	}
	if (type == 'r')
	{
		ft_close_fd(&p->w);
		stream->fd = p->r;
	}
	else
	{
		ft_close_fd(&p->r);
		stream->fd = p->w;
	}
	stream->pid = pid;
	return (stream);
}

t_file	*ft_popen(char *cmd, char type)
{
	t_file	*stream;
	pid_t	pid;
	t_pipe	p;

	if (type != 'r' && type != 'w')
		return (NULL);
	if (!ft_init_pipe(&p))
		return (NULL);
	pid = fork();
	if (pid == -1)
	{
		ft_close_pipe(&p);
		return (NULL);
	}
	if (pid == 0)
		child_exec(cmd, type, &p);
	stream = init_stream(&p, pid, type);
	return (stream);
}
