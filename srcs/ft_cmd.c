/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:41:23 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/22 15:31:46 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(char **path, char *cmd)
{
	char	*path_cmd;
	char	*ret_cmd;
	int		i;

	i = -1;
	if (access(cmd, X_OK) != -1)
		return (cmd);
	path_cmd = ft_strjoin("/", cmd);
	while (path[++i])
	{
		ret_cmd = ft_strjoin(path[i], path_cmd);
		if (access(ret_cmd, X_OK) != -1)
		{
			free(path_cmd);
			return (ret_cmd);
		}
		free(ret_cmd);
	}
	free(path_cmd);
	return (0);
}

char	**get_cmd_arg(t_line *line)
{
	t_cmd	*tmp;
	char	**str_tmp;
	char	**ret;
	int		i;

	i = 0;
	tmp = line->cmd;
	while (tmp && i < line->size)
	{
		if (tmp->type == pipe)
			i++;
		tmp = tmp->next;
	}
	i = 0;
	while (tmp && tmp->type != pipe)
	{
		str_tmp = ret;
		if (tmp->type == cmd)
			ret = add_back(str_tmp, tmp->str, ++i);
		if (tmp->type == red)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (ret);
}
