/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:29:00 by wocheon           #+#    #+#             */
/*   Updated: 2023/01/27 15:09:08 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_err(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

t_cmd	*push_back(t_line *line)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		exit_err("minishell: malloc error");
	new->status = line->status;
	new->next = NULL;
	new->str = "\0";
	new->quotes = 0;
	new->dollar = 0;
	new->pipe = 0;
	new->type = 0;
	return (new);
}

char	*ft_strjoin_char(char const *s1, char s2)
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

int	check_type(char *rd_line, int i)
{
	if (rd_line[i] == ' ')
		return (0);
	else if (rd_line[i] == '\'')
		return (0);
	else if (rd_line[i] == '>')
		return (0);
	else if (rd_line[i] == '<')
		return (0);
	else if (!ft_strncmp(rd_line + i, ">>", 2))
		return (0);
	else if (!ft_strncmp(rd_line + i, "<<", 2))
		return (0);
	return (1);
}

void	check_quotes(char *rd_line, int i)
{
	char	c;

	c = rd_line[i];
	while (rd_line[i])
	{
		if (c == rd_line[i])
			i++;
	}
	exit_err("minishell: quotes error");
}

int	single_quote(t_line *line, t_cmd *cmd, char *rd_line, int i)
{
	t_cmd	*next;
	int		j;

	j = 0;
	check_quotes(rd_line, i);
	while (rd_line[i + ++j])
	{
		if (cmd->quotes == 1 && check_type(rd_line, i + j))
			cmd->str = ft_strjoin_char(cmd->str, rd_line[i + j]);
		else if (cmd->quotes == 1 && !check_type(rd_line, i + j))
			break ;
		else if (rd_line[i + j] != '\'')
			cmd->str = ft_strjoin_char(cmd->str, rd_line[i + j]);
		else
		{
			if (check_type(rd_line, i + j + 1))
			{
				cmd->str = ft_strjoin_char(cmd->str, rd_line[i + ++j]);
				cmd->quotes = 1;
			}
			else
				break ;
		}
	}
	next = push_back(line);
	cmd->next = next;
	return (j);
}

int	pipes(t_line *line, t_cmd *cmd, char *rd_line, int i)
{
	t_cmd	*pipe_node;
	t_cmd	*after_pipe;
	int		j;

	j = 0;
	if (rd_line[i + 1] == '|')
		exit_err("minishell: pipe error");
	if (rd_line[i - 1] != ' ')
	{
		pipe_node = push_back(line);
		cmd->next = pipe_node;
		cmd = cmd->next;
	}
	cmd->str = ft_strjoin_char(cmd->str, '|');
	cmd->type = 2;
	j++;
	after_pipe = push_back(line);
	cmd->next = after_pipe;
	return (j);
}

int	spaces(t_line *line, t_cmd *cmd, char *rd_line, int i)
{
	t_cmd	*next;
	int		j;

	j = 0;
	while (rd_line[i + j])
	{
		if (rd_line[i + j] == ' ')
			j++;
		else
			break ;
	}
	next = push_back(line);
	cmd->next = next;
	return (j);
}

int	join_char(t_line *line, t_cmd *cmd, char *rd_line, int i)
{
	t_cmd	*next;
	int		j;

	j = 0;
	while (rd_line[i + j])
	{
		if (rd_line[i + j] == ' ')
			break ;
		else if (rd_line[i + j] == '|')
			break ;
		else if (rd_line[i + j] == '>')
			break ;
		else if (rd_line[i + j] == '<')
			break ;
		else if (!ft_strncmp(rd_line + i, ">>", 2))
			break ;
		else if (!ft_strncmp(rd_line + i, "<<", 2))
			break ;
		else
			cmd->str = ft_strjoin_char(cmd->str, rd_line[i + j]);
		j++;
	}
	next = push_back(line);
	cmd->next = next;
	return (j);
}

int	check_red(char *rd_line, int i)
{
	if (rd_line[i] == '>')
		return (0);
	else if (rd_line[i] == '<')
		return (0);
	else if (!ft_strncmp(rd_line + i, ">>", 2))
		return (0);
	else if (!ft_strncmp(rd_line + i, "<<", 2))
		return (0);
	return (1);
}

int	redirections(t_line *line, t_cmd *cmd, char *rd_line, int i)
{
	t_cmd	*next;
	int		j;

	j = 0;
	if (!ft_strncmp(rd_line + i, ">>", 2))
	{
		cmd->str = ft_strjoin(cmd->str, ">>");
		cmd->type = 1;
		j = 2;
	}
	else if (!ft_strncmp(rd_line + i, "<<", 2))
	{
		cmd->str = ft_strjoin(cmd->str, "<<");
		cmd->type = 1;
		j = 2;
	}
	else if (rd_line[i] == '>')
	{
		cmd->str = ft_strjoin_char(cmd->str, '>');
		cmd->type = 1;
		j = 1;
	}
	else if (rd_line[i] == '<')
	{
		cmd->str = ft_strjoin_char(cmd->str, '<');
		cmd->type = 1;
		j = 1;
	}
	next = push_back(line);
	cmd->next = next;
	cmd = cmd->next;
	return (j);
}

void	tokenize(t_line *line, t_cmd *cmd, char *rd_line)
{
	int	i;

	i = 0;
	while (rd_line[i])
	{
		if (rd_line[i] == ';' || rd_line[i] == '\\')
			exit_err("minishell: syntax error");
		else if (rd_line[i] == '\'')
			i += single_quote(line, cmd, rd_line, i);
		// else if (rd_line[i] == '\"')
		
		else if (rd_line[i] == ' ')
			i += spaces(line, cmd, rd_line, i);
		else if (rd_line[i] == '|')
			i += pipes(line, cmd, rd_line, i);
		else if (!check_red(rd_line, i))
			i += redirections(line, cmd, rd_line, i);
		else
			i += join_char(line, cmd, rd_line, i);
		cmd = cmd->next;
	}
}
// space after pipe,
// command before and after pipe without space

void	parse(t_line *line, char *rd_line, char **envp)
{
	t_cmd	*new;

	(void) envp;
	line->cmd = push_back(line);
	tokenize(line, line->cmd, rd_line);
	new = line->cmd;
	while (new)
	{
		printf("%s \n", new->str);
		new = new->next;
	}
}