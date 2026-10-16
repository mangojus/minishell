#ifndef LIBSTR_H
# define LIBSTR_H

# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include "libmem.h"
# include "libchar.h"

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strcnt(char const *s, char c);
int			ft_stridx(const char *s, const char *set);
size_t		ft_strspn(const char *s, const char *set);
char		*ft_strpbrk(const char *s, const char *set);
void		ft_strstrip(char *s, char *set);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char		*ft_strtrim(char const *s, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strtok(char *s, const char *set, char **endptr);
size_t		ft_strtokcnt(const char *s, const char *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
long		ft_strtol(const char *nptr, char **endptr);
int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
long long	ft_atoll(const char *nptr);
char		*ft_itoa(int n);
char		*ft_ltoa(long n);
char		*ft_ultoa(unsigned long n);
char		*ft_itoa_base(int nbr, char *base);
char		*ft_ltoa_base(long nbr, char *base);
char		*ft_lltoa_base(long long nbr, char *base);
char		*ft_ultoa_base(unsigned long nbr, char *base);
char		*ft_strquote(const char *s);
double		ft_atof(const char *nptr);
bool		ft_isnumber(char *s);
int			ft_tablen(char **tab);

#endif
