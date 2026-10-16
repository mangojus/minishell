#include "minishell.h"

static bool	parse_digits(const char **sptr, int sign, unsigned long long *num)
{
	if (!ft_isdigit((unsigned char)**sptr))
		return (false);
	while (**sptr && ft_isdigit((unsigned char)**sptr))
	{
		*num = (*num * 10) + (**sptr - '0');
		if ((sign == -1 && *num > (unsigned long)LONG_MAX + 1)
			|| (sign == 1 && *num > LONG_MAX))
			return (false);
		(*sptr)++;
	}
	return (true);
}

static bool	is_strict_atol(const char *s, long *out)
{
	unsigned long long	num;
	const char			*sptr;
	int					sign;

	num = 0;
	sign = 1;
	sptr = s;
	while (*sptr && ft_isspace((unsigned char)*sptr))
		sptr++;
	if (ft_ischarset(*sptr, "+-"))
	{
		if (*sptr == '-')
			sign = -1;
		sptr++;
	}
	if (!parse_digits(&sptr, sign, &num))
		return (false);
	while (*sptr && ft_isspace((unsigned char)*sptr))
		sptr++;
	if (*sptr != '\0')
		return (false);
	*out = sign * (long)num;
	return (true);
}

t_err	ft_exit(char **args, t_data *data)
{
	long	exit_code;	

	if (data->cmd->type == CMD)
		ft_rprintf(1, "exit\n");
	if (!args[1])
	{
		free_all_data(data);
		exit((unsigned char)data->last_status);
	}
	if (!is_strict_atol(args[1], &exit_code))
	{
		ft_rprintf(2, "msh: exit: %s: numeric argument required\n", args[1]);
		free_all_data(data);
		exit((unsigned char)ERR_SYNTAX);
	}
	if (args[2])
	{
		ft_rprintf(2, "msh: exit: too many arguments\n");
		return (ERR_BASH);
	}
	free_all_data(data);
	exit((unsigned char)exit_code);
}
