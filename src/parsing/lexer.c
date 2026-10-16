#include "minishell.h"

static char	*create_token(char *buf, char **endptr)
{
	char	*token;
	t_idx	i;

	ft_bzero(&i, sizeof(i));
	if (check_quotes(buf, &i.end))
		;
	else if (ft_ischarset(buf[i.end], "><|&;()"))
	{
		if ((buf[i.end] == '<' && buf[i.end + 1] == '<') || \
				(buf[i.end] == '>' && buf[i.end + 1] == '>'))
			i.end += 2;
		else
			++i.end;
	}
	else
	{
		while (buf[i.end] && !ft_ischarset(buf[i.end], " \t\n\r><|"))
			++i.end;
	}
	token = ft_strndup(buf, i.end);
	if (!token)
		return (NULL);
	if (endptr && buf)
		*endptr = &buf[i.end];
	return (token);
}

static t_tok	*add_token(char *content, t_tok **lst)
{
	t_tok	*token;
	t_tok	*tmp;

	token = ft_calloc(1, sizeof(t_tok));
	if (!token)
		return (NULL);
	token->fd = -1;
	token->content = content;
	token->type = CMD;
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
		token->prev = tmp;
	}
	else if (!*lst)
		*lst = token;
	return (token);
}

bool	tokenize_list(char *line, t_tok **lst)
{
	t_tok	*tmp;
	char	*token;
	char	*endptr;
	char	*it;

	it = line;
	while (it && *it)
	{
		while (ft_isspace(*it))
			++it;
		if (!*it)
			break ;
		token = create_token(it, &endptr);
		if (!token)
			return (false);
		tmp = add_token(token, lst);
		if (!tmp)
			return (free(token), false);
		it = endptr;
	}
	return (true);
}
