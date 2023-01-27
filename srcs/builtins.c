/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:29:32 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/27 13:20:35 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(char	**cmd_arg)
{
	int		i;

	write(1, "exit\n", 5);
	if (cmd_arg[1] && cmd_arg[2])
		print_error("exit:too many arguments", 1);
	else if (cmd_arg[1])
	{
		i = -1;
		while (cmd_arg[1][++i])
		{
			if (!ft_isdigit(cmd_arg[1][i]))
				print_error("exit error", 255);
		}
		exit(ft_atoi(cmd_arg[1]));
	}
	exit(0);
}

void	echo_line(char	**cmd_arg)
{
	int		i;
	int		flag;

	flag = 0;
	if (cmd_arg[1])
	{
		i = 1;
		if (!ft_strncmp(cmd_arg[i], "-n", ft_strlen(cmd_arg[1])))
		{
			flag = 1;
			i++;
		}
		while (cmd_arg[i])
		{
			ft_printf("%s", cmd_arg[i++]);
			if (cmd_arg[i])
				write(1, " ", 1);
		}
	}
	if (!flag)
		write(1, "\n", 1);
}

int	builtins_check(char	*str)
{
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	return (0);
}

void	builtins_exec(char **cmd_arg)
{
	if (!ft_strncmp(cmd_arg[0], "echo", ft_strlen(cmd_arg[0])))
		echo_line(cmd_arg);
	if (!ft_strncmp(cmd_arg[0], "pwd", ft_strlen(cmd_arg[0])))
		get_pwd();
	if (!ft_strncmp(cmd_arg[0], "unset", ft_strlen(cmd_arg[0])))
		unset_env(cmd_arg);
	if (!ft_strncmp(cmd_arg[0], "cd", ft_strlen(cmd_arg[0])))
		change_dir(cmd_arg);
	if (!ft_strncmp(cmd_arg[0], "export", ft_strlen(cmd_arg[0])))
		export_env(cmd_arg);
	if (!ft_strncmp(cmd_arg[0], "exit", ft_strlen(cmd_arg[0])))
		exit_shell(cmd_arg);
	if (!ft_strncmp(cmd_arg[0], "env", ft_strlen(cmd_arg[0])))
		print_env(cmd_arg);
}

void	builtins_set(t_line *line)
{
	char	**cmd_arg;

	get_io(line, NULL, 0);
	cmd_arg = get_cmd_arg(line, 0);
	builtins_exec(cmd_arg);
	free(cmd_arg);
	backup_fd(line);
}
