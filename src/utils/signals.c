#include "minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signo = 1;
}

void	sigint_heredoc(int signo)
{
	(void)signo;
	rl_done = 1;
	g_signo = 1;
}

void	restore_parent_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	install_sigint_hd(void)
{
	signal(SIGINT, sigint_heredoc);
}
