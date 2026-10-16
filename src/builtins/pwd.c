#include "minishell.h"

t_err	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", pwd);
	else
	{
		if (errno == ENOMEM)
			return (ERR_MALLOC);
		ft_rprintf(2, "pwd: error retrieving current directory: ");
		ft_rprintf(2, "getcwd: cannot access parent directories: ");
		ft_rprintf(2, "%s\n", strerror(errno));
		return (ERR_BASH);
	}
	free(pwd);
	return (ERR_OK);
}
