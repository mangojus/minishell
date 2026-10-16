#include "minishell.h"

bool	check_line(t_data *data)
{
	int	i;

	if (!ft_strcmp(data->line, ":"))
	{
		data->status = ERR_OK;
		return (false);
	}
	if (!ft_strcmp(data->line, "!"))
	{
		data->status = ERR_BASH;
		return (false);
	}
	i = 0;
	if (check_all_quotes(data->line, &i) == 1)
	{
		data->status = ERR_SYNTAX;
		ft_dprintf(2, "msh: syntax error: unclosed quote\n");
		return (false);
	}
	return (true);
}

int	check_all_quotes(char *buf, int *index)
{
	char	quote;
	int		i;
	int		count;

	i = *index;
	while (buf[i] && !ft_ischarset(buf[i], "'\""))
		i++;
	if (!buf[i] || !ft_ischarset(buf[i], "'\""))
		return (0);
	quote = buf[i];
	count = 1;
	i++;
	while (buf[i] && buf[i] != quote)
		i++;
	if (buf[i] == quote)
	{
		count++;
		i++;
	}
	while (buf[i] && !ft_ischarset(buf[i], "'\""))
		i++;
	count += check_all_quotes(buf, &i);
	*index = i;
	return (count % 2);
}

int	check_quotes(char *s, int *index)
{
	char	quote;
	int		i;
	int		count;

	i = *index;
	while (s[i] && !ft_isspace(s[i]) && !ft_ischarset(s[i], "><|'\""))
		i++;
	if (!s[i] || !ft_ischarset(s[i], "'\""))
		return (0);
	quote = s[i];
	count = 1;
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
	{
		count++;
		i++;
	}
	while (s[i] && !ft_isspace(s[i]) && !ft_ischarset(s[i], "><|'\""))
		i++;
	count += check_quotes(s, &i);
	*index = i;
	return (count % 2);
}

bool	check_list(t_tok *lst)
{
	while (lst)
	{
		if (lst->next)
		{
			if ((!(lst->type & (CMD | PIPE | DELIM | FD | VAR))
					&& !(lst->next->type & (CMD | FD | DELIM | VAR)))
				|| ((lst->type & PIPE) && (lst->next->type & PIPE)))
			{
				error_print(ERR_SYNTAX, lst->next->content);
				return (false);
			}
		}
		if (lst->type & PIPE && (!lst->prev || !lst->next))
		{
			error_print(ERR_SYNTAX, lst->content);
			return (false);
		}
		else if (!(lst->type & (CMD | FD | DELIM | VAR)) && !lst->next)
		{
			error_print(ERR_SYNTAX, "newline");
			return (false);
		}
		lst = lst->next;
	}
	return (true);
}
