#include "minishell.h"

static t_tok	*link_fds(t_tok **lst)
{
	t_tok	*fds;
	t_tok	*it;

	fds = NULL;
	while (*lst && (*lst)->next)
	{
		it = *lst;
		if (it->type & (RIN | ROUT | APP | HDOC))
		{
			it->next->type = it->type;
			tok_dlstremove(&it);
			tok_dlstlink(it->prev, it->next);
			if (it->next)
				*lst = it->next;
			else
				*lst = it->prev;
			tok_dlstadd_back(&fds, it);
			it->next = NULL;
		}
		else
			*lst = (*lst)->next;
	}
	*lst = tok_dlsthead(*lst);
	return (fds);
}

/*
	static int j = 0; //malloc
	if (j == 2) // malloc	
	{
		ft_free_sptr(cmd->args); // malloc fail test
		cmd->args = NULL; // malloc fail test
	}
	j++; //malloc*/
static bool	add_cmd(t_tok **tok_lst, t_cmd **cmd_lst, bool flag)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (false);
	if (flag)
		cmd->type = PIPE;
	else
		cmd->type = CMD;
	cmd->fds = link_fds(tok_lst);
	cmd->args = tok_dlstconvert(*tok_lst);
	tok_dlstfree(tok_lst);
	if (!cmd->args)
		return (cmd_dlstfree(&cmd), false);
	cmd->index = cmd_dlstsize(*cmd_lst);
	if (*cmd_lst)
		cmd_dlstlink(cmd_dlstlast(*cmd_lst), cmd);
	else
		*cmd_lst = cmd;
	return (true);
}

bool	build_cmd_list(t_tok **tok_lst, t_cmd **cmd_lst)
{
	t_tok	*it;

	it = *tok_lst;
	while (it)
	{
		if (it->type == PIPE)
		{
			tok_dlstremove(&it);
			tok_dlstsplit(it->prev, it);
			if (!add_cmd(tok_lst, cmd_lst, true))
			{
				tok_dlstfree(&it);
				return (false);
			}
			*tok_lst = tok_dlsthead(it);
		}
		else
			it = it->next;
	}
	if (!add_cmd(tok_lst, cmd_lst, false))
		return (false);
	*cmd_lst = cmd_dlsthead(*cmd_lst);
	*tok_lst = NULL;
	return (true);
}
