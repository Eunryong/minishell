#include "minishell.h"

int	exit_shell(int i) //exit || ctrl d
{
	write(1, "exit\n", 5);
	exit(0);
	return (i);
}

int	change_dir(t_line *line) //dir변경 공백일때 홈
{
	int	result;

	if (!line->cmd->next->str)
	{
		result = chdir("/Users/eunrlee/");
	}
	else
		result = chdir(line->cmd->next->str);
	if (result == -1)
		perror(line->cmd->next->str);
	return (1);
}

int	get_pwd(int i)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (i);
}

int	echo_line(char *line)
{
	int	i;

	i = 7;
	while (line[++i] && line[i] != '\n')
	{
		write(1, &line[i], 1);
	}
	return (1);
}

int	builtins_check(t_line *line, int status)
{
	t_cmd	*tmp;

	tmp = line->cmd;
	if (!ft_strncmp(tmp->str, "echo", ft_strlen(tmp->str)))
		return (echo_line(line));
	if (!ft_strncmp(tmp->str, "pwd", ft_strlen(tmp->str)))
		return (get_pwd(1));
	if (!ft_strncmp(tmp->str, "unset", ft_strlen(tmp->str)))
		return (unset_env(line));
	if (!ft_strncmp(tmp->str, "cd", ft_strlen(tmp->str)))
		return (change_dir(line));
	if (!ft_strncmp(tmp->str, "export", ft_strlen(tmp->str)))
		return (add_env(line));
	if (!ft_strncmp(tmp->str, "exit", ft_strlen(tmp->str)))
		return (exit_shell(1));
	if (!ft_strncmp(tmp->str, "env", ft_strlen(tmp->str)))
		return (display_env(line));
	return (0);
}
