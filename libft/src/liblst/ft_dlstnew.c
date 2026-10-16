#include "liblst.h"

t_dlst	*ft_dlstnew(int content)
{
	t_dlst	*new;

	new = malloc(sizeof(t_dlst));
	if (!new)
		return (NULL);
	new->content = content;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
