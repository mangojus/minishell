#ifndef LIBFD_H
# define LIBFD_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libmem.h"

typedef struct s_file
{
	pid_t	pid;
	int		fd;
}	t_file;

typedef struct s_pipe
{
	int	r;
	int	w;
}	t_pipe;

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_close_fd(int *fd);
bool	ft_init_pipe(t_pipe *p);
void	ft_close_pipe(t_pipe *p);
void	ft_close_pipeline(t_pipe *pipeline, int nb);
t_file	*ft_popen(char *cmd, char type);
int		ft_pclose(t_file *stream);

#endif
