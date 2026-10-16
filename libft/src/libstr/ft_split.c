#include "libstr.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	start;
	size_t	end;
	size_t	i;

	tab = ft_calloc((ft_count(s, c) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	end = 0;
	while (s[end])
	{
		while (s[end] && s[end] == c)
			end++;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		if (end > start)
		{
			tab[i] = ft_substr(s, start, end - start);
			if (!tab[i++])
				return (ft_free_sptr(tab), NULL);
		}
	}
	return (tab);
}
