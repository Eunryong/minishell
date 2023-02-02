/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 03:57:07 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/02 16:50:30 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	seperate_type(t_cmd **cmd, char *str, int size, int i)
{
	t_cmd	*tmp;

	if (i != 0)
	{
		(*cmd)->str = ft_substr(str, 0, i);
		tmp = seperate_cmd(cmd);
		tmp->str = ft_substr(str, i, size);
		(*cmd) = (*cmd)->next;
	}
	else if (i == 0)
		(*cmd)->str = ft_substr(str, 0, size);
	if (str[i] == '|')
		(*cmd)->type = 2;
	else
		(*cmd)->type = 1;
	if (str[i + size])
	{
		tmp = seperate_cmd(cmd);
		tmp->str = ft_strdup(str + i + size);
	}
}

void	seperate_as_type(t_line *line)
{
	t_cmd	*cmd;
	char	*str;
	int		i;

	i = 0;
	cmd = line->cmd;
	while (cmd)
	{
		if (cmd->quote == 0)
		{
			i = 0;
			while (cmd->str[i])
			{
				if (check_type(cmd->str, i))
				{
					str = cmd->str;
					seperate_type(&cmd, str, check_type(cmd->str, i), i);
					free(str);
					break ;
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
}
