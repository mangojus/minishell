#include "libstr.h"

static const char	*preprocess(const char *nptr, int *sign)
{
	while (ft_isspace(*nptr) != 0)
		nptr++;
	if (*nptr == '-')
	{
		*sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	return (nptr);
}

static const char	*convert_str(const char *nptr, int base, long *res)
{
	int	digit;

	while (*nptr)
	{
		if (ft_isdigit(*nptr))
			digit = *nptr - '0';
		else if (*nptr >= 'a' && *nptr <= 'f')
			digit = *nptr - 'a' + 10;
		else if (*nptr >= 'A' && *nptr <= 'F')
			digit = *nptr - 'A' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		if (*res >= (LONG_MAX / base))
			return (NULL);
		if (*res <= (LONG_MIN / base))
			return (NULL);
		*res = *res * base + digit;
		nptr++;
	}
	return (nptr);
}

long	ft_strtol(const char *nptr, char **endptr)
{
	long	res;
	int		sign;
	int		base;

	res = 0;
	sign = 1;
	base = 10;
	nptr = preprocess(nptr, &sign);
	if (nptr[0] == '0' && nptr[1] == 'x')
	{
		nptr += 2;
		base = 16;
	}
	if (base == 10 && !ft_isdigit(*nptr))
		return (0);
	nptr = convert_str(nptr, base, &res);
	if (endptr && nptr)
		*endptr = (char *)nptr;
	return (res * sign);
}
