/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:12:39 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/24 23:16:30 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_red(t_cmd *cmd, int *f_flag, int *b_flag)
{
	int	fd;

	if (!ft_strncmp(cmd->str, "<" , ft_strlen(cmd->str)))
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

	f_flag = 0;
	b_flag = 0;
	tmp = line->cmd;
	while (tmp)
	{
		if (tmp->type == red)
		{
			set_red(tmp, &f_flag, &b_flag);
			tmp = tmp -> next;
		}
		tmp = tmp -> next;
	}
	if (!f_flag && i != 0)
		dup2(fd[0], STDIN_FILENO);
	if (!b_flag && i != line->size - 1)
		dup2(fd[1], STDOUT_FILENO);
}
