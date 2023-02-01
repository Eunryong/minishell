/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:12:39 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/29 18:50:02 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_fd(t_line *line)
{
	dup2(line->input, STDIN_FILENO);
	dup2(line->output, STDOUT_FILENO);
}

void	set_heredoc_fd(int i)
{
	char	*filename;
	int		fd;

	filename = get_filename(i);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error(filename, 1, 1);
	dup2(fd, STDIN_FILENO);
	free(filename);
	close(fd);
}

void	set_red_front(t_cmd *cmd, int *i)
{
	int	fd;

	if (!ft_strncmp(cmd->str, "<<", 2))
		set_heredoc_fd((*i)++);
	else if (!ft_strncmp(cmd->str, "<", ft_strlen(cmd->str)))
	{
		fd = open(cmd->next->str, O_RDONLY);
		if (fd == -1)
			printf(cmd->next->str, 1, 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	set_red_back(t_cmd *cmd, int *flag)
{
	int	fd;

	if (!ft_strncmp(cmd->str, ">", ft_strlen(cmd->str)))
	{
		*flag = 1;
		fd = open(cmd->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			printf(cmd->next->str, 1, 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (!ft_strncmp(cmd->str, ">>", 2))
	{
		*flag = 2;
		fd = open(cmd->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			printf(cmd->next->str, 1, 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	get_io(t_line *line, int *fd, int size)
{
	int		flag;
	t_cmd	*tmp;
	int		heredoc_i;

	flag = 0;
	heredoc_i = 0;
	tmp = get_pipe(line, size);
	while (tmp && tmp->type != pip)
	{
		if (tmp->type == red)
		{
			set_red_front(tmp, &heredoc_i);
			set_red_back(tmp, &flag);
			tmp = tmp -> next;
		}
		tmp = tmp -> next;
	}
	if (fd && !flag && size != line->size - 1)
		dup2(fd[1], STDOUT_FILENO);
	if (fd)
	{
		close(fd[1]);
		close(fd[0]);
	}
}
