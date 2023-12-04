/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:29:32 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 16:29:20 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(char	**cmd_arg, int size)
{
	int		i;

	if (size == 1)
		write(1, "exit\n", 5);
	if (cmd_arg[1])
	{
		i = -1;
		while (cmd_arg[1][++i])
		{
			if (!ft_isdigit(cmd_arg[1][i]))
				syntax_error("exit: numeric argument required", 255, 1);
		}
		if (cmd_arg[1] && cmd_arg[2])
		{
			syntax_error("exit: too many arguments", 1, 0);
			return ;
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
		while (cmd_arg[i])
		{
			if (!check_str_n(cmd_arg[i]))
				break ;
			i++;
		}
		if (i != 1)
			flag = 1;
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
	if (!ft_strlen(str))
		return (0);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (2);
	if (!ft_strcmp(str, "env"))
		return (1);
	return (0);
}

void	builtins_exec(char **cmd_arg, int size)
{
	g_env->status = 0;
	if (!ft_strcmp(cmd_arg[0], "echo"))
		echo_line(cmd_arg);
	if (!ft_strcmp(cmd_arg[0], "pwd"))
		get_pwd();
	if (!ft_strcmp(cmd_arg[0], "unset"))
		unset_env(cmd_arg);
	if (!ft_strcmp(cmd_arg[0], "cd"))
		change_dir(cmd_arg);
	if (!ft_strcmp(cmd_arg[0], "export"))
		export_env(cmd_arg);
	if (!ft_strcmp(cmd_arg[0], "exit"))
		exit_shell(cmd_arg, size);
	if (!ft_strcmp(cmd_arg[0], "env"))
		print_env(cmd_arg);
}

int	builtins_set(t_line *line)
{
	char	**cmd_arg;
	int		i;

	get_io(line, NULL, 0);
	cmd_arg = get_cmd_arg(line, 0);
	builtins_exec(cmd_arg, line->size);
	i = -1;
	while (cmd_arg[++i])
		free(cmd_arg[i]);
	free(cmd_arg);
	if (builtins_check(line->cmd->str) == 2)
		return (-2);
	backup_fd(line);
	return (1);
}
