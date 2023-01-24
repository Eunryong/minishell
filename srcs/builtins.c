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

int	echo_line(t_line *line)
{
	t_cmd	*tmp;
	int		flag;

	tmp = line->cmd;
	flag = 0;
	if (tmp->next)
	{
		if (!ft_strncmp(tmp->next->str, "-n", ft_strlen(tmp->next->str)))
		{
			flag = 1;
			tmp = tmp->next;
		}
		tmp = tmp->next;
		while (tmp)
		{
			ft_printf("%s", tmp->str);
			if (tmp->next)
				write(1, " ", 1);
			tmp = tmp->next;
		}
	}
	if (!flag)
		write(1, "\n", 1);
	return (1);
}

int	builtins_check(t_line *line)
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
		return (export_env(line));
	if (!ft_strncmp(tmp->str, "exit", ft_strlen(tmp->str)))
		return (ft_printf("exit"));
	if (!ft_strncmp(tmp->str, "env", ft_strlen(tmp->str)))
		return (print_env());
	return (0);
}
