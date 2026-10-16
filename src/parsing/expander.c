#include "minishell.h"

static char	*compare_var(char *token, int len, t_env *env)
{
	while (env)
	{
		if (len == (int)ft_strlen(env->key) && !ft_memcmp(token, env->key, len))
		{
			if (env->value)
				return (ft_strdup(env->value));
			else
				return (ft_strdup(""));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

static char	*replace_var(char *tok, int len, t_data *data)
{
	char	*var;
	char	*tmp;

	if (tok[0] == '"')
	{
		var = ft_strndup(tok + 1, len - 2);
		if (!var)
			return (NULL);
		tmp = expand_token(var, data, true);
		free(var);
		if (!tmp)
			return (NULL);
		var = ft_strquote(tmp);
		free(tmp);
	}
	else if (ft_isdigit(tok[1]))
		var = ft_strndup(&tok[2], len - 2);
	else if (tok[1] == '?')
		var = ft_itoa(data->last_status);
	else if (!tok[1] || (!ft_isalpha(tok[1]) && !ft_ischarset(tok[1], "'\"")))
		var = ft_strdup("$");
	else
		var = compare_var(tok + 1, len - 1, data->env);
	return (var);
}

static bool	scan_token(char *token, t_idx *i, bool quote)
{
	bool	flag;	
	int		tmp;

	flag = false;
	if (!quote && token[i->start] == '\'')
		i->len = ft_stridx(token + i->start + 1, "'") + 2;
	else if (token[i->start] == '\"')
	{
		i->len = ft_stridx(token + i->start + 1, "\"") + 2;
		tmp = ft_stridx(token + i->start, "$");
		if (tmp != -1 && tmp < i->len)
			flag = true;
	}
	else if (token[i->start] == '$')
	{
		i->len = ft_stridx(token + i->start + 1, SHELL_CHAR) + 1;
		if (token[i->start + 1] == '$')
			i->len += 1;
		flag = true;
	}
	else
		i->len = ft_stridx(token + i->start, "\"$");
	if (i->len <= 0)
		i->len = ft_strlen(token + i->start);
	return (flag);
}

char	*expand_token(char *token, t_data *data, bool quote)
{
	char	*new_dst;
	char	*dst;
	char	*tmp;
	t_idx	i;

	dst = NULL;
	ft_bzero(&i, sizeof(i));
	while (token[i.start])
	{
		if (scan_token(token, &i, quote))
			tmp = replace_var(token + i.start, i.len, data);
		else
			tmp = ft_strndup(token + i.start, i.len);
		if (!tmp)
			return (free(dst), NULL);
		new_dst = ft_strjoin(dst, tmp);
		free(dst);
		free(tmp);
		if (!new_dst)
			return (NULL);
		dst = new_dst;
		i.start += i.len;
	}
	return (dst);
}

bool	expand_list(t_tok **lst, t_data *data)
{
	t_tok	*it;
	t_tok	*new_lst;
	char	*new_token;

	it = *lst;
	while (it)
	{
		if (it->type == VAR)
		{
			new_token = expand_token(it->content, data, false);
			if (!new_token)
				return (false);
			new_lst = NULL;
			if (!tokenize_list(new_token, &new_lst))
				return (free(new_token), false);
			free(new_token);
			it = tok_dlstreplace(lst, it, new_lst);
		}
		else
			it = it->next;
	}
	*lst = tok_dlsthead(*lst);
	return (true);
}
