#include "minishell.h"

int	main2(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*res;
	int		fd[2];
	int		i;

	if (!init_data(&data, argc, argv, envp))
		return (EXIT_FAILURE);
	fd[0] = open("tests//tests/tester.txt", O_RDONLY);
	fd[1] = open("tests/tests/solution.txt", O_RDONLY);
	data.line = "";
	i = 1;
	while (data.line != NULL)
	{
		data.line = ft_gnl(fd[0]);
		if (data.line)
			data.line[ft_stridx(data.line, "\n")] = '\0';
		printf(YLW"%d: %s\n"RESET, i, data.line);
		fflush(stdout);
		printf(BLU"%d: ", i);
		fflush(stdout);
		if (!data.line)
		{
			free_all_data(&data);
			break;
		}
		if (parser(&data))
			exec_line(&data);
		free_data(&data);
		res = ft_gnl(fd[1]);
		if (res)
			res[ft_stridx(res, "\n")] = '\0';
		printf(GRN"%d: %s\n"RESET, i, res);
		free(res);
		i++;
		data.line = "";
	}
	close(fd[0]);
	close(fd[1]);
	return (data.status);
}

int	main1(int argc, char **argv, char **envp)
{
	t_data	data;

	if (!init_data(&data, argc, argv, envp))
		return (EXIT_FAILURE);
	restore_parent_signals();
	while (true)
	{
		data.line = readline("minishell> ");
		if (!data.line)
			break ;
		if (g_signo)
		{
			data.last_status = ERR_SIGINT;
			g_signo = 0;
		}
		if (*data.line)
			add_history(data.line);
		if (parser(&data))
			exec_line(&data);
		free_data(&data);
		data.last_status = data.status;
	}
	write(1, "exit\n", 5);
	clear_history();
	free_all_data(&data);
	return (data.last_status);
}

int	main(int argc, char **argv, char **envp)
{
	if (argv[1] && !ft_strcmp(argv[1], "1"))
		return (main1(argc, argv, envp));
	else if (argv[1] && !ft_strcmp(argv[1], "2"))
		return (main2(argc, argv, envp));
	else
		printf("wrongs args for main\n");
	return (1);
}
