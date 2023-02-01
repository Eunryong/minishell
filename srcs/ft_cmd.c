/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:41:23 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 16:47:07 by eunrlee          ###   ########.fr       */
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
	if (!path)
		print_error(cmd, 127, 1);
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

t_cmd	*get_pipe(t_line *line, int size)
{
	int		i;
	t_cmd	*tmp;

	tmp = line->cmd;
	i = 0;
	while (tmp && i < size)
	{
		if (tmp->type == pip)
			i++;
		tmp = tmp->next;
	}
	return (tmp);
}

char	**get_cmd_arg(t_line *line, int size)
{
	t_cmd	*tmp;
	char	**ret;
	char	*str_tmp;
	int		i;

	tmp = get_pipe(line, size);
	ret = 0;
	i = 0;
	while (tmp && tmp->type != pip)
	{
		if (tmp->type == cmd)
		{
			str_tmp = ft_strdup(tmp->str);
			ret = push_back_arr(ret, str_tmp, ++i);
		}
		if (tmp->type == red)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (ret);
}
