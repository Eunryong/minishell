/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:21:48 by wocheon           #+#    #+#             */
/*   Updated: 2023/01/31 15:33:23 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_quote(t_line *line, char *rd_line)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	while (rd_line[i] != '\"')
		i++;
	cmd = push_back(line);
	cmd->str = ft_substr(rd_line, 1, i - 1);
	cmd->quote = 2;
	return (i);
}

int	small_quote(t_line *line, char *rd_line)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	while (rd_line[i] != '\'')
		i++;
	cmd = push_back(line);
	cmd->str = ft_substr(rd_line, 1, i - 1);
	cmd->quote = 1;
	return (i);
}

int	get_arg(t_line *line, char *rd_line)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	while (rd_line[i] != '\"' && rd_line[i] != '\'' && rd_line[i])
	{
		if (rd_line[i] == '\\' || rd_line[i] == ';')
			line->syntax = 1;
		i++;
	}
	cmd = push_back(line);
	cmd->str = ft_substr(rd_line, 0, i);
	return (i - 1);
}

void	seperate_quote(t_line *line, char *rd_line)
{
	int	i;

	i = 0;
	while (rd_line[i])
	{
		if (rd_line[i] == '\"')
			i += double_quote(line, rd_line + i);
		else if (rd_line[i] == '\'')
			i += small_quote(line, rd_line + i);
		else
			i += get_arg(line, rd_line + i);
		i++;
	}
}
