/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:41:20 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/27 14:46:53 by eunrlee          ###   ########.fr       */
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

void	excute(t_line *line, int *fd, int i)
{
	char	**cmd_arg;
	char	*cmd;
	char	**path;

	get_io(line, fd, i);
	path = get_path();
	cmd_arg = get_cmd_arg(line, i);
	if (builtins_check(cmd_arg[0]))
	{
		builtins_exec(cmd_arg);	
		exit(0);
	}
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
	t_cmd	*tmp;

	i = -1;
	tmp = line->cmd;
	if (builtins_check(tmp->str) && line->size == 1)
		return (builtins_set(line));
	while (++i < line->size && tmp)
	{
		if (pipe(fd) < 0)
			print_error("pipe error", 1);
		pid = fork();
		if (pid == -1)
			print_error("fork error", 1);
		if (pid == 0)
			excute(line, fd, i);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		tmp = tmp->next;
	}
	backup_fd(line);
	wait_all(line, pid);
}
