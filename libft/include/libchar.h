#ifndef LIBCHAR_H
# define LIBCHAR_H

# include <stdbool.h>

bool	ft_isalpha(int c);
bool	ft_isdigit(int c);
bool	ft_isalnum(int c);
bool	ft_isascii(int c);
bool	ft_isprint(int c);
bool	ft_isspace(int c);
bool	ft_isblank(int c);
bool	ft_ischarset(int c, const char *set);
int		ft_toupper(int c);
int		ft_tolower(int c);

#endif
