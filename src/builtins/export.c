#include "minishell.h"

static bool	is_valid_identifier(char *s)
{
	size_t	i;

	i = 1;
	if (!s || !(ft_isalpha((unsigned char)s[0]) || s[0] == '_'))
		return (false);
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
			return (false);
		i ++;
	}
	return (true);
}

static t_err	print_sorted_env(t_env *env)
{
	t_env	**arr;
	int		count;
	int		i;

	if (!env)
		return (ERR_OK);
	count = env_dlstsize(env);
	arr = create_env_array(env, count);
	if (!arr)
		return (ERR_MALLOC);
	sort_env_array(arr, count);
	i = 0;
	while (i < count)
	{
		printf("export %s", arr[i]->key);
		if (arr[i]->value)
			printf("=\"%s\"", arr[i]->value);
		printf("\n");
		i++;
	}
	free(arr);
	return (ERR_OK);
}

static bool	update_env(t_env **env, t_env **new, bool append)
{
	t_env	*old;
	char	*dst;

	old = env_dlstfind(*env, (*new)->key);
	if (!old)
	{
		env_dlstadd_front(env, *new);
		*new = NULL;
		return (true);
	}
	else if (!(*new)->value)
		return (true);
	else if (append)
		dst = ft_strjoin(old->value, (*new)->value);
	else
		dst = ft_strdup((*new)->value);
	if (!dst)
		return (false);
	free(old->value);
	old->value = dst;
	return (true);
}

static t_env	*parse_export_argument(char *arg, bool *append)
{
	t_env	*new;
	char	*ptr;
	int		len;

	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		*append = true;
	ptr = ft_strchr(arg, '=');
	if (ptr)
		len = ptr - arg - *append;
	else
		len = ft_strlen(arg);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strndup(arg, len);
	if (!new->key)
		return (env_dlstfree(&new), NULL);
	if (ptr)
	{
		new->value = ft_strdup(ptr + 1);
		if (!new->value)
			return (env_dlstfree(&new), NULL);
	}
	return (new);
}

t_err	ft_export(char **a, t_env **env)
{
	t_env	*new;
	int		i;
	bool	append;
	t_err	status;

	status = ERR_OK;
	if (!a[1])
		return (print_sorted_env(*env));
	i = 0;
	while (a[++i])
	{
		append = false;
		new = parse_export_argument(a[i], &append);
		if (!new)
			return (ERR_MALLOC);
		if (!is_valid_identifier(new->key))
		{
			status = ERR_BASH;
			ft_dprintf(2, "msh: export: `%s': not a valid identifier\n", a[i]);
		}
		else if (!update_env(env, &new, append))
			return (ERR_MALLOC);
		env_dlstfree(&new);
	}
	return (status);
}
