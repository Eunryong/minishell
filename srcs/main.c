#include "minishell.h"

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
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	struct termios	term;

	(void)argv;
	(void)envp;
	tcgetattr(STDIN_FILENO, &term);
	main_init(argc); //구조체 초기화
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && !is_space(line))
		{
			//parsing
			set_excute(line, envp);
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
