#ifndef COMMAND_H

# define COMMAND_H

# include "type.h"
# include "token.h"
# include "libstr.h"

typedef struct s_cmd
{
	char			**args;
	t_tok			*fds;
	int				index;
	enum e_cmd_type	type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

int		cmd_dlstsize(t_cmd *lst);
t_cmd	*cmd_dlsthead(t_cmd *lst);
t_cmd	*cmd_dlstlast(t_cmd *lst);
void	cmd_dlstfree(t_cmd **lst);
void	cmd_dlstlink(t_cmd *a, t_cmd *b);

#endif
