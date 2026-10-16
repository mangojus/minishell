#include "token.h"

char	**tok_dlstconvert(t_tok *lst)
{
	char	**tab;
	int		i;

	tab = ft_calloc((tok_dlstsize(lst) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (lst)
	{
		tab[i] = ft_strdup(lst->content);
		if (!tab[i])
		{
			ft_free_sptr(tab);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	return (tab);
}
