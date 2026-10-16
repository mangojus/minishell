#include "env.h"

void	sort_env_array(t_env **arr, int count)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	*get_env_value(char **envp, char *name)
{
	size_t	len;
	int		i;

	if (!envp || !name)
		return (NULL);
	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

bool	create_env_list(char **envp, t_env **env)
{
	char	*it;
	char	*endptr;
	char	*key;
	char	*value;

	endptr = NULL;
	while (*envp)
	{
		it = ft_strdup(*envp);
		if (!it)
			return (env_dlstfree(env), false);
		key = ft_strtok(it, "=", &endptr);
		value = ft_strtok(NULL, "", &endptr);
		if (!env_dlstadd_back(env, env_dlstnew(key, value)))
		{
			free(it);
			return (false);
		}
		free(it);
		envp++;
	}
	return (true);
}

t_env	**create_env_array(t_env *env, int count)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		arr[i] = env;
		env = env->next;
		i++;
	}
	return (arr);
}
