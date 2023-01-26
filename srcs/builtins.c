/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:29:32 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/26 19:52:02 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_line *line)
{
	t_cmd	*tmp;
	int		i;

	tmp = line->cmd->next;
	write(1, "exit\n", 5);
	if (tmp)
	{
		i = -1;
		while (tmp->str[++i])
		{
			if (!ft_isdigit(tmp->str[i]))
				print_error("exit error", 255);
		}
		exit(ft_atoi(tmp->str));
	}
	exit(0);
}

void	echo_line(t_line *line)
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
}

int	builtins_check(t_line *line)
{
	t_cmd	*tmp;

	tmp = line->cmd;
	if (!ft_strncmp(tmp->str, "echo", ft_strlen(tmp->str)))
		return (1);
	if (!ft_strncmp(tmp->str, "pwd", ft_strlen(tmp->str)))
		return (1);
	if (!ft_strncmp(tmp->str, "unset", ft_strlen(tmp->str)))
		return (1);
	if (!ft_strncmp(tmp->str, "cd", ft_strlen(tmp->str)))
		return (1);
	if (!ft_strncmp(tmp->str, "export", ft_strlen(tmp->str)))
		return (1);
	if (!ft_strncmp(tmp->str, "exit", ft_strlen(tmp->str)))
		return (1);
	if (!ft_strncmp(tmp->str, "env", ft_strlen(tmp->str)))
		return (1);
	return (0);
}

void	builtins_exec(t_line *line)
{
	t_cmd	*tmp;

	tmp = line->cmd;
	if (!ft_strncmp(tmp->str, "echo", ft_strlen(tmp->str)))
		echo_line(line);
	if (!ft_strncmp(tmp->str, "pwd", ft_strlen(tmp->str)))
		get_pwd();
	if (!ft_strncmp(tmp->str, "unset", ft_strlen(tmp->str)))
		unset_env(line);
	if (!ft_strncmp(tmp->str, "cd", ft_strlen(tmp->str)))
		change_dir(line);
	if (!ft_strncmp(tmp->str, "export", ft_strlen(tmp->str)))
		export_env(line);
	if (!ft_strncmp(tmp->str, "exit", ft_strlen(tmp->str)))
		exit_shell(line);
	if (!ft_strncmp(tmp->str, "env", ft_strlen(tmp->str)))
		print_env(line);
}

void	builtins_set(t_line *line, int flag)
{
	get_io(line, NULL, 0);
	builtins_exec(line);
	if (flag)
		backup_fd(line);
}
