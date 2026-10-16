#include "minishell.h"

static int	handle_redir(const char *path, t_type type, int *dst_fd)
{
	int	new_fd;

	if (!dst_fd || !path)
		return (-1);
	new_fd = open_fd((char *)path, type);
	if (new_fd == -1)
		return (-1);
	if (*dst_fd != -1)
		close_fd(dst_fd);
	*dst_fd = new_fd;
	return (0);
}

bool	manage_fds(t_cmd *cmd, t_fds *fds)
{
	t_tok	*tok;

	tok = cmd->fds;
	while (tok)
	{
		if (tok->type == HDOC)
		{
			if (tok->fd == -1)
				return (false);
			if (fds->infile != -1)
				close_fd(&fds->infile);
			fds->infile = tok->fd;
		}
		else if ((tok->type == RIN
				&& handle_redir(tok->content, tok->type, &fds->infile) == -1)
			|| ((tok->type == ROUT || tok->type == APP)
				&& handle_redir(tok->content, tok->type, &fds->outfile) == -1))
			return (false);
		tok = tok->next;
	}
	return (true);
}

int	open_fd(char *filename, t_type type)
{
	t_err	status;
	int		fd;

	fd = -1;
	if (type == RIN)
		fd = open(filename, O_RDONLY);
	else if (type == ROUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APP)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		status = set_err_to_errno();
		if (status == ERR_NOENT || status == ERR_ACCESS)
			error_print(status, filename);
		else
			perror("open fd");
	}
	return (fd);
}
