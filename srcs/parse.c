/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:29:00 by wocheon           #+#    #+#             */
/*   Updated: 2023/01/27 14:27:15 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_err(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

char	*ft_join_char(char const *s1, char s2)
{
	char	*ret;
	size_t	s1_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(&s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, &s2, 2);
	return (ret);
}

int	get_quotes(char c, int quotes)
{
	int	result;

	result = quotes;
	if (c == '\'')
	{
		if (quotes == 1)
			result = 0;
		else if (quotes == 2)
			result = 2;
		else
			result = 1;
	}
	else if (c == '\"')
	{
		if (quotes == 2)
			result = 0;
		else if (quotes == 1)
			result = 1;
		else
			result = 2;
	}
	return (result);
}

t_cmd	*push_back_cmd(t_line *line)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		exit_err("malloc error!");
	new->next = NULL;
	new->str = "\0";
	new->type = 0;
	new->dollar = 0;
	new->quotes = 0;
	new->pipe = 0;
	new->status = line->status;
	return (new);
}

t_cmd	*make_new_node(t_line *line)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		exit_err("malloc errer");
	new->next = NULL;
	new->str = "\0";
	new->type = 0;
	new->dollar = 0;
	new->pipe = 0;
	new->status = line->status;
	return (new);
}

t_cmd	*split_pipe(t_line *line, t_cmd *cmd, char c1, char c2)
{
	t_cmd	*new;
	t_cmd	*new_next;

	cmd->pipe = 0;
	new = make_new_node(line);
	cmd->str = ft_join_char(cmd->str, '\0');
	new->str = ft_join_char(new->str, c1);
	cmd->next = new;
	new->pipe = 1;
	new->type = pip;
	line->size++;
	cmd = cmd->next;
	if (c2 != ' ')
	{
		new_next = make_new_node(line);
		cmd->next = new_next;
		cmd = cmd->next;
	}
	return (cmd);
}

t_cmd	*split_space(t_line *line, t_cmd *cmd, char c)
{
	t_cmd	*new;

	cmd->str = ft_join_char(cmd->str, '\0');
	if (c != ' ' && c != '\0' && c != '|')
	{
		new = make_new_node(line);
		cmd->next = new;
		cmd = cmd->next;
	}
	return (cmd);
}

void	split_quotes(t_cmd *cmd, char c1, char c2)
{
	if (c2 == '\'' && cmd->dollar == 1)
	{
		cmd->dollar = 2;
		cmd->str = ft_join_char(cmd->str, c1);
	}
	else if (c2 == '\"' && cmd->dollar == 1)
	{
		cmd->dollar = 3;
		cmd -> str = ft_join_char(cmd->str, c1);
	}
	else
		cmd -> str = ft_join_char(cmd->str, c1);
}

void	check_dollar(t_cmd *cmd, char c1, char c2)
{
	if (c1 == c2)
		exit_err("syntax error");
	cmd->dollar = 1;
}

void	tokenize(t_line *line, t_cmd *cmd, char *rd_line)
{
	while (*rd_line)
	{
		cmd->quotes = get_quotes(*rd_line, cmd->quotes);
		if ((*rd_line == ';' || *rd_line == '\\') && cmd->quotes == 0)
			exit_err("syntax error");
		else if (cmd->quotes == 0 && *rd_line == '|' && cmd->pipe == 1)
			exit_err("syntax error");
		else if (cmd->quotes == 0 && *rd_line == '|' && *(rd_line + 1) == '\0')
			exit_err("syntax error");
		else if (cmd->quotes == 0 && *rd_line == '|' && cmd->pipe == 0)
			cmd = split_pipe(line, cmd, *rd_line, *(rd_line + 1));
			//pipe value->0
		else if (cmd->quotes == 0 && *rd_line == ' ')
			cmd = split_space(line, cmd, *(rd_line + 1));
		else if (cmd->quotes != 0)
			split_quotes(cmd, *rd_line, *(rd_line + 1));
		else if (cmd->quotes == 0 && *rd_line == '$')
			check_dollar(cmd, *rd_line, *(rd_line + 1));
		else if (cmd->quotes == 0)
			cmd->str = ft_join_char(cmd->str, *rd_line);
		else if (cmd->quotes != 0 && *rd_line == '\0')
			exit_err("syntax error");
		else if (*rd_line == '\0')
			cmd->str = ft_join_char(cmd->str, '\0');
		rd_line++;
	}
}
// space after pipe,
// command before and after pipe without space

void	parse(t_line *line, char *rd_line, char **envp)
{
	(void) envp;
	line->cmd = push_back_cmd(line);
	tokenize(line, line->cmd, rd_line);
}
