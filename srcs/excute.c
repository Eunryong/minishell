/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:41:20 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 16:49:37 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_all(pid_t last_pid)
{
	int		temp;
	pid_t	pid;

	pid = 1;
	while (pid != -1)
	{
		pid = wait(&temp);
		if (pid == last_pid)
		{
			if (WIFEXITED(temp))
				g_env->status = WEXITSTATUS(temp);
			else if (WIFSIGNALED(temp))
				g_env->status = WTERMSIG(temp) + 128;
			if (g_env->status == 131)
				ft_putstr_fd("Quit: 3\n", 2);
		}
	}
	return (1);
}

char	**get_path(void)
{
	t_env	*tmp;

	tmp = g_env;
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = get_path();
	cmd_arg = get_cmd_arg(line, i);
	if (!cmd_arg || !cmd_arg[0][0])
		cmd_error("", 127, 1);
	if (builtins_check(cmd_arg[0]))
	{
		builtins_exec(cmd_arg, line->size);
		exit(g_env->status);
	}
	cmd = get_cmd(path, cmd_arg[0]);
	if (!cmd)
		cmd_error(cmd_arg[0], 127, 1);
	if (execve(cmd, cmd_arg, env_to_arr()) == -1)
		print_error("execve error", 126, 1);
}

void	close_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int	set_excute(t_line *line)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	i = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (builtins_check(line->cmd->str) && line->size == 1)
		return (builtins_set(line));
	while (++i < line->size)
	{
		if (pipe(fd) < 0)
			print_error("pipe error", 1, 1);
		pid = fork();
		if (pid == -1)
			print_error("fork error", 1, 1);
		if (pid == 0)
			excute(line, fd, i);
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd[0], fd[1]);
	}
	backup_fd(line);
	return (wait_all(pid));
}
