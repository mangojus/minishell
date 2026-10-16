#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 10
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*ft_gnl(int fd);

void	gnl_bzero(void *s, size_t n);
int		gnl_strchr(const char *s, int c);
size_t	gnl_strlen(const char *s);
void	*gnl_memmove(void *dest, const void *src, size_t n);
char	*gnl_strjoin(char const *s1, char const *s2);

#endif
