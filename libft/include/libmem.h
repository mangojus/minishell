#ifndef LIBMEM_H
# define LIBMEM_H

# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_arr
{
	void	*data;
	size_t	size;
	size_t	capacity;
}	t_arr;

void	ft_nullfree(void **ptr);
void	ft_free_sptr(char **str);
void	ft_free_nptr(int **num, size_t size);
void	ft_free_pptr(void **ptr, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);
bool	ft_push_value(t_arr *arr, void *value, size_t value_size);
bool	ft_grow_vec(t_arr *arr, size_t value_size);

#endif
