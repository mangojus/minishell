#include "libstr.h"

static double	parse_unsigned_float(const char *s, size_t *i)
{
	double	res;
	double	div;

	res = 0.0;
	while (s[*i] && ft_isdigit(s[*i]))
		res = res * 10.0 + (s[(*i)++] - '0');
	if (s[*i] == '.')
	{
		(*i)++;
		div = 10.0;
		while (s[*i] && ft_isdigit(s[*i]))
		{
			res += (s[*i] - '0') / div;
			div *= 10.0;
			(*i)++;
		}
	}
	return (res);
}

double	ft_atof(const char *nptr)
{
	size_t	i;
	int		sign;
	double	res;

	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	res = parse_unsigned_float(nptr, &i);
	return (res * (double)sign);
}
