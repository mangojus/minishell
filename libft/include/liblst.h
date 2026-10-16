#ifndef LIBLST_H
# define LIBLST_H

# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));

typedef struct s_dlst
{
	int				content;
	size_t			index;
	struct s_dlst	*next;
	struct s_dlst	*prev;
}	t_dlst;

t_dlst	*ft_dlstnew(int content);
void	ft_dlstadd_front(t_dlst **lst, t_dlst *new);
void	ft_dlstadd_back(t_dlst **lst, t_dlst *new);
int		ft_dlstsize(t_dlst *lst);
void	ft_dlstlink(t_dlst *l1, t_dlst *l2);
void	ft_dlstsplit(t_dlst *l1, t_dlst *l2);
t_dlst	*ft_dlsthead(t_dlst *lst);
t_dlst	*ft_dlstlast(t_dlst *lst);
void	ft_dlstfree(t_dlst **lst);
void	ft_dlstdelone(t_dlst *lst, void (*del)(int));
void	ft_dlstclear(t_dlst **lst, void (*del)(int));
void	ft_dlstiter(t_dlst *lst, void (*f)(int));

#endif
