#include "minishell.h"

t_env	*env;

void	print_error(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

int	is_space(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (0);
		line++;
	}
	return (1);
}

void	main_init(int argc)
{
	struct termios	term;

	if (argc != 1)
		print_error("argument input error", 126);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	make_env();
}

int	main(int argc, char **argv, char **envp)
{
	char			*rd_line;
	struct termios	term;
	t_line			line;

	(void)argv;
	(void)envp;
	tcgetattr(STDIN_FILENO, &term);
	main_init(argc);
	line.input = dup(STDIN_FILENO);
	line.output = dup(STDOUT_FILENO);
	while (1)
	{
		line.size = 1;
		rd_line = readline("minishell $ ");
		if (!rd_line)
			break ;
		if (*rd_line != '\0')
			add_history(rd_line);
		if (*rd_line != '\0' && !is_space(rd_line))
		{
			parse(&line, rd_line, envp);
			set_excute(&line);
			clear_cmd(&line);
		}
		free(rd_line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
