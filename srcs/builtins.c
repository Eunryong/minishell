#include "minishell.h"

int	exit_shell(int i) //exit || ctrl d
{
	write(1, "exit\n", 5);
	exit(0);
	return (i);
}

int	change_dir(char *line) //dir변경 공백일때 홈
{
	int	result;

	if (!line[3])
	{
		result = chdir("/Users/eunrlee/");
	}
	else
		result = chdir(line + 3);
	if (result == -1)
		perror(line + 3);
	return (1);
}

int	get_pwd(int i) //getcwd를 이용해 작업중인 경로 buf사이즈는 수정
{
	char	*pwd;
	char	buf[100];
	
	pwd = getcwd(buf, 100);
	ft_printf("%s\n", pwd);
	return (i);
}

int	echo_line(char *line)//-n옵션
{
	int	i;

	i = 7;
	while (line[++i] && line[i] != '\n')
	{
		write(1, &line[i], 1);
	}
	return (1);
}

int	builtins_check(char *line, int status) // 체크후 아닐시 리턴 0
{
	if (!ft_strncmp(line, "echo -n ", 8))
		return (echo_line(line));
	if (!ft_strncmp(line, "pwd", 3))
		return (get_pwd(1));
	if (!ft_strncmp(line, "unset", 5))
		return (remove_env(line));
	if (!ft_strncmp(line, "cd ", 3))
		return (change_dir(line));
	if (!ft_strncmp(line, "export", 6))
		return (add_env(line));
	if (!ft_strncmp(line, "exit", 4))
		return (exit_shell(1));
	if (!ft_strncmp(line, "env", 3))
		return (display_env(line));
	return (0);
}
