#include "minishell.h"

static void	set_type(t_tok *lst)
{
	if (*(lst->content) == '|')
		lst->type = PIPE;
	else if (ft_strncmp(lst->content, "<<", 2) == 0)
		lst->type = HDOC;
	else if (ft_strncmp(lst->content, ">>", 2) == 0)
		lst->type = APP;
	else if (*(lst->content) == '<')
		lst->type = RIN;
	else if (*(lst->content) == '>')
		lst->type = ROUT;
	else if (lst->prev && lst->prev->type & (RIN | ROUT | APP))
		lst->type = FD;
	else if (lst->prev && lst->prev->type & HDOC)
		lst->type = DELIM;
	else if (ft_ischarset(*(lst->content), "&;()"))
		lst->type = UNDEF;
	else if (ft_strchr(lst->content, '$'))
		lst->type = VAR;
	else
		lst->type = CMD;
}

static void	strip_quotes(char *str)
{
	char	*it;
	char	*endptr;
	char	quote;

	it = ft_strpbrk(str, "'\"");
	if (!it)
		return ;
	quote = *it;
	ft_memmove(it, it + 1, ft_strlen(it + 1) + 1);
	endptr = ft_strchr(it, quote);
	if (!endptr)
		return ;
	ft_memmove(endptr, endptr + 1, ft_strlen(endptr + 1) + 1);
	strip_quotes(endptr);
	return ;
}

static void	strip_quotes_helper(t_tok *tok)
{
	if (tok && tok->content)
		strip_quotes(tok->content);
}

static t_err	parse_list(t_data *data)
{
	if (!tokenize_list(data->line, &data->tok))
		return (ERR_MALLOC);
	tok_dlstiter(data->tok, set_type);
	if (!check_list(data->tok))
		return (ERR_SYNTAX);
	if (!expand_list(&data->tok, data))
		return (ERR_MALLOC);
	tok_dlstiter(data->tok, strip_quotes_helper);
	if (!build_cmd_list(&data->tok, &data->cmd))
		return (ERR_MALLOC);
	return (ERR_OK);
}

bool	parser(t_data *data)
{
	if (!check_line(data))
		return (false);
	data->status = parse_list(data);
	free(data->line);
	data->line = NULL;
	if (data->status == ERR_MALLOC)
		error_exit("parsing", data);
	else if (data->status != ERR_OK)
		return (false);
	return (true);
}
