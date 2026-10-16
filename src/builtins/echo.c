#include "minishell.h"

static bool	is_valid_flag(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (false);
	i++;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

t_err	ft_echo(char **arg)
{
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	while (arg[i] && is_valid_flag(arg[i]))
	{
		n_flag = true;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (ERR_OK);
}
