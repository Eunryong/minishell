/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:12:39 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/27 13:59:19 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_fd(t_line *line)
{
	dup2(line->input, STDIN_FILENO);
	dup2(line->output, STDOUT_FILENO);
}

void	set_heredoc_fd(int i, int *f_flag)
{
	char	*filename;
	int		fd;

	*f_flag = 2;
	filename = get_filename(i);
	fd = open(filename, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	free(filename);
	close(fd);
}

void	set_red(t_cmd *cmd, int *f_flag, int *b_flag, int *i)
{
	int	fd;

	if (!ft_strncmp(cmd->str, "<<", ft_strlen(cmd->str)))
		set_heredoc_fd((*i)++, f_flag);
	else if (!ft_strncmp(cmd->str, "<", ft_strlen(cmd->str)))
	{
		*f_flag = 1;
		fd = open(cmd->next->str, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (!ft_strncmp(cmd->str, ">", ft_strlen(cmd->str)))
	{
		*b_flag = 1;
		fd = open(cmd->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (!ft_strncmp(cmd->str, ">>", ft_strlen(cmd->str)))
	{
		*b_flag = 2;
		fd = open(cmd->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	get_io(t_line *line, int *fd, int i)
{
	int		f_flag;
	int		b_flag;
	t_cmd	*tmp;
	int		heredoc_i;

	f_flag = 0;
	b_flag = 0;
	tmp = line->cmd;
	heredoc_i = 0;
	while (tmp)
	{
		if (tmp->type == red)
		{
			set_red(tmp, &f_flag, &b_flag, &heredoc_i);
			tmp = tmp -> next;
		}
		tmp = tmp -> next;
	}
	if (fd)
	{
		if (!b_flag && i != line->size - 1)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}
