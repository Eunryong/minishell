/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:32:33 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/27 14:20:59 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(char **cmd_arg)
{
	int	i;

	i = -1;
	while (cmd_arg[++i])
		free(cmd_arg[i]);
	free(cmd_arg);
}

void	clear_cmd(t_line *line)
{
	t_cmd	*tmp;
	t_cmd	*pre;
	int		i;
	int		fd;
	char	*filename;

	tmp = line->cmd;
	while (tmp)
	{
		pre = tmp;
		free(tmp->str);
		tmp = tmp->next;
		free(pre);
	}
	line->cmd = 0;
	fd = 0;
	i = 0;
	while (fd != -1)
	{
		filename = get_filename(i++);
		fd = access(filename, F_OK);
		if (fd == 0)
			unlink(filename);
		free(filename);
	}
}
