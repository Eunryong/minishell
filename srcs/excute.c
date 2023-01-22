/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:41:20 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/22 16:40:45 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_all(t_line *line, pid_t last_pid)
{
	int		temp;
	int		status;
	pid_t	pid;

	pid = 1;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == last_pid)
			line->status = temp;
	}
	return (status >> 8);
}

char	**get_path(char **env)
{
	while (*env)
	{
		if (ft_strncmp(env, "PATH", 4))
			break ;
		env++;
	}
	if (!env)
		return (0);
	return (ft_split(env + 5, ':'));
}

void	excute(t_line *line)
{
	char	*cmd_arg;
	char	*cmd

	cmd_arg = get_cmd_arg(line);
	cmd = get_cmd(get_path(line->env) ,cmd_arg[0]);
	if (!cmd)
		print_error("command not found", 127);
	if (execve(cmd, cmd_arg, line->env) == -1)
		print_error("execve error", 1);
}

void	set_excute(t_line *line)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	i = -1;
	while (++i < line->size && line->cmd)
	{
		if (pipe(fd) == -1)
			print_error("pipe error", 1);
		pid = fork();
		if (pid == -1)
			print_error("fork error", 1);
		if (pid == 0)
		{
			get_io(line, fd, i);
			excute(line);
		}
		close(fd[0]);
		close(fd[1]);
		line->cmd = line->cmd->next;
	}
	wait_all(pid);
}
