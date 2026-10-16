#include "libstr.h"

static bool	parse_number_body(char *s, int *i, bool *has_digit)
{
	bool	is_float;

	is_float = false;
	*has_digit = false;
	while (s[*i])
	{
		if (ft_isdigit(s[*i]))
			*has_digit = true;
		else if (s[*i] == '.')
		{
			if (is_float)
				return (false);
			is_float = true;
		}
		else if (ft_isspace(s[*i]))
		{
			while (ft_isspace(s[*i]))
				(*i)++;
			return (true);
		}
		else
			return (false);
		(*i)++;
	}
	return (true);
}

bool	ft_isnumber(char *s)
{
	int		i;
	bool	has_digit;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!parse_number_body(s, &i, &has_digit))
		return (false);
	if (s[i] != '\0' || !has_digit)
		return (false);
	return (true);
}
