#ifndef ENV_H

# define ENV_H

# include <stdio.h>
# include <stdlib.h>
# include "libstr.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

t_env	*env_dlstnew(char *key, char *value);
t_env	**env_dlstadd_front(t_env **lst, t_env *node);
t_env	**env_dlstadd_back(t_env **lst, t_env *node);
int		env_dlstsize(t_env *env);
t_env	*env_dlsthead(t_env *lst);
t_env	*env_dlstlast(t_env *lst);
t_env	*env_dlstremove(t_env **env);
t_env	*env_dlstfind(t_env *env, char *key);
void	env_dlstfree(t_env **env);
void	env_dlstlink(t_env *a, t_env *b);
char	**env_dlstconvert(t_env *env);
t_env	**create_env_array(t_env *env, int count);
char	*get_env_value(char **envp, char *name);
bool	create_env_list(char **envp, t_env **env);
void	sort_env_array(t_env **arr, int count);

#endif
