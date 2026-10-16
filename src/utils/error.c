#include "minishell.h"

t_err	set_err_to_errno(void)
{
	if (errno == EACCES)
		return (ERR_ACCESS);
	if (errno == EISDIR)
		return (ERR_ISDIR);
	if (errno == ENOEXEC)
		return (ERR_NOEXEC);
	if (errno == ENOMEM)
		return (ERR_MALLOC);
	if (errno == ENOENT)
		return (ERR_NOENT);
	return (ERR_BASH);
}

int	set_err_to_exit(t_err err)
{
	if (err == ERR_ACCESS || err == ERR_ISDIR || err == ERR_NOEXEC)
		return (126);
	if (err == ERR_NOTFOUND || err == ERR_NOENT)
		return (127);
	return (err);
}

void	error_exit(char *str, t_data *data)
{
	t_err	err;

	if (data->status != 0)
		err = data->status;
	else
		err = set_err_to_errno();
	error_print(err, str);
	free_all_data(data);
	exit(set_err_to_exit(err));
}

void	error_print(t_err err, char *str)
{
	if (err == ERR_NOENT)
		ft_rprintf(2, "msh: %s: No such file or directory\n", str);
	else if (err == ERR_ACCESS)
		ft_rprintf(2, "msh: %s: Permission denied\n", str);
	else if (err == ERR_ISDIR)
		ft_rprintf(2, "msh: %s: Is a directory\n", str);
	else if (err == ERR_NOEXEC)
		ft_rprintf(2, "msh: %s: Exec format error\n", str);
	else if (err == ERR_NOTFOUND)
		ft_rprintf(2, "msh: %s: Command not found\n", str);
	else if (err == ERR_SYNTAX)
		ft_rprintf(2, "msh: syntax error near unexpected token `%s'\n", str);
	else if (err == ERR_MALLOC)
		ft_rprintf(2, "msh: %s: malloc: critical failure\n", str);
	//else if (err >= 128)
		//print_signal(err - 128);
	else
		perror(str);
}
