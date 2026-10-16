#include "env.h"

char	**env_dlstconvert(t_env *env)
{
	char	**tab;
	char	*tmp;
	int		i;

	tab = ft_calloc(env_dlstsize(env) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (ft_free_sptr(tab), NULL);
		tab[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		if (!tab[i])
			return (ft_free_sptr(tab), NULL);
		env = env->next;
		i++;
	}
	return (tab);
}
