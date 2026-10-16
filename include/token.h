#ifndef TOKEN_H

# define TOKEN_H

# include <stdlib.h>
# include "type.h"
# include "libstr.h"

typedef struct s_tok
{
	char			*content;
	int				fd;
	enum e_cmd_type	type;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

void	tok_dlstadd_back(t_tok **lst, t_tok *new);
int		tok_dlstsize(t_tok *lst);
t_tok	*tok_dlsthead(t_tok *lst);
t_tok	*tok_dlstlast(t_tok *lst);
void	tok_dlstlink(t_tok *a, t_tok *b);
void	tok_dlstsplit(t_tok *a, t_tok *b);
void	tok_dlstremove(t_tok **lst);
void	tok_dlstfree(t_tok **lst);
t_tok	*tok_dlstreplace(t_tok **lst, t_tok *old, t_tok *new);
void	tok_dlstiter(t_tok *lst, void (*f)(t_tok *));
char	**tok_dlstconvert(t_tok *lst);

#endif
