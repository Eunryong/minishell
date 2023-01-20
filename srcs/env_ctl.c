#include "minishell.h"

int	display_env(char *line) // env
{
	(void)line;
	ft_printf ("환경변수 띄우기\n");
	return (1);
}

int	add_env(char *line) // export
{
	(void)line;
	ft_printf("환경변수 더하기, 마지막에 넣고 널처리\n");
	ft_printf("공백없을때 이상한값 띄우기\n");
	return (1);
}

int	remove_env(char *line) // unset
{
	(void)line;
	ft_printf("환경변수 지우기, 지우고 처리해주기\n");
	return (1);
}

int	print_exit(int status)
{
	ft_printf("%d\n", status);
	return (1);
}
