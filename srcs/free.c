/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:32:33 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 15:30:26 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	if (s3)
		free(s3);
}

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

	tmp = line->cmd;
	while (tmp)
	{
		pre = tmp;
		free(tmp->str);
		tmp = tmp->next;
		free(pre);
	}
	line->cmd = 0;
}
