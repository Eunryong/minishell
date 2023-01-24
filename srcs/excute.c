/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:41:20 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/24 23:26:46 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_all(t_line *line, pid_t last_pid)
{
	int		temp;
	pid_t	pid;

	pid = 1;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == last_pid)
			line->status = temp;
	}
	return (line->status >> 8);
}

char	**get_path(void)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	return (ft_split(tmp->val, ':'));
}

void	excute(t_line *line)
{
	char	**cmd_arg;
	char	*cmd;
	char	**path;

	path = get_path();
	cmd_arg = get_cmd_arg(line);
	cmd = get_cmd(path, cmd_arg[0]);
	if (!cmd)
		print_error("command not found", 127);
	if (execve(cmd, cmd_arg, env_to_arr()) == -1)
		print_error("execve error", 1);
}

void	set_excute(t_line *line)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	i = -1;
	line->size = 1;
	if (!builtins_check(line))
	{	
		while (++i < line->size && line->cmd)
		{
			if (pipe(fd) < 0)
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
		wait_all(line, pid);
	}
}
