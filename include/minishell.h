#ifndef MINISHELL_H

# define MINISHELL_H

# define BLU "\033[1;34m"
# define GRN "\033[1;32m"
# define YLW "\033[1;33m"
# define RESET "\033[0m"
# define SHELL_CHAR " '\"#%&$*+-.,:;<=>~[](){}|\\´`/^!"

# include "libft.h"
# include "token.h"
# include "command.h"
# include "env.h"
# include "type.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <ctype.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>

extern volatile sig_atomic_t	g_signo;

typedef enum e_err
{
	ERR_OK = 0,
	ERR_BASH = 1,
	ERR_SYNTAX = 2,
	ERR_MALLOC = 6,
	ERR_ISDIR,
	ERR_NOEXEC,
	ERR_ACCESS = 126,
	ERR_NOTFOUND = 127,
	ERR_NOENT,
	ERR_SIGINT = 130,
	ERR_SIGQUIT = 131,
	ERR_SIGKILL = 137,
}	t_err;

typedef struct s_index
{
	int	start;
	int	end;
	int	len;
}	t_idx;

typedef struct s_fds
{
	int		infile;
	int		outfile;
	int		pipe1[2];
	int		pipe2[2];
	int		p[2];
}	t_fds;

typedef struct s_data
{
	char	*line;
	t_tok	*tok;
	t_cmd	*cmd;
	t_env	*env;
	char	*cwd;
	t_err	status;
	int		last_status;
}	t_data;

// SIGNALS

void	sigint_handler(int signo);
void	print_signal(int sig);
void	ignore_parent_signals(void);
void	restore_parent_signals(void);
void	child_signals(void);
void	install_sigint_hd(void);
void	sigint_heredoc(int sig);

// PARSING

bool	parser(t_data *data);
bool	tokenize_list(char *buf, t_tok **lst);
bool	expand_list(t_tok **lst, t_data *data);
char	*expand_token(char *token, t_data *data, bool quote);
bool	build_cmd_list(t_tok **tok_lst, t_cmd **cmd_lst);

int		check_quotes(char *s, int *index);
int		check_all_quotes(char *buf, int *index);
bool	check_line(t_data *data);
bool	check_list(t_tok *lst);

// BUILTINS

t_err	ft_pwd(void);
t_err	ft_cd(char **args, t_env **env);
t_err	ft_env(char **args, t_env **env);
t_err	ft_echo(char **arg);
t_err	ft_exit(char **args, t_data *data);
t_err	ft_export(char **args, t_env **env);
t_err	ft_unset(char **args, t_env **env);

// EXEC

int		handle_single_builtin(t_cmd *cmd, t_fds *fds, t_data *data);
bool	is_builtin(const char *cmd);
t_err	exec_builtin(char **args, t_data *data);

void	exec_line(t_data *data);
void	execute_cmd(char **args, t_data *data);

bool	cancel_on_heredoc(t_data *data);

int		child(t_cmd *cmd, t_fds *fds, t_data *data);

bool	manage_fds(t_cmd *cmd, t_fds *fds);
int		open_fd(char *filename, t_type type);
void	close_fd(int *fd);
void	close_fds(t_fds *fds);
void	close_previous_pipe_parent(t_cmd *cmd, t_fds *fds);
void	close_pipe(int fds[2]);
int		get_pipe(size_t cmd_index);

t_err	dup2_redirect(int old_fd, int new_fd);
t_err	wait_child(pid_t pid);
int		wait_children(int nb_cmds, int last_pid);
int		checked_pipe(int p[2], t_fds *fds, t_data *data);
int		open_next_pipe(t_cmd *cmd, int count, t_fds *fds, t_data *data);

// UTILS

bool	init_data(t_data *data, int argc, char **argv, char **envp);
void	free_data(t_data *data);
void	free_all_data(t_data *data);

void	error_exit(char *str, t_data *data);
void	error_print(t_err err, char *str);
t_err	set_err_to_errno(void);
int		set_err_to_exit(t_err err);

#endif
