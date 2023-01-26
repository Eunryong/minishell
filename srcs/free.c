/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:32:33 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/26 19:47:50 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	line->cmd = 0;
}
