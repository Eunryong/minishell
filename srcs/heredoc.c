/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:55:31 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/02 12:41:21 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_heredoc_file(char *limiter, char *filename)
{
	char	*str;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error("open error", 1, 1);
	while (1)
	{
		signal(SIGINT, sig_exit);
		ft_putstr_fd("heredoc > ", 1);
		str = get_next_line(0);
		if (!str)
			break ;
		if (!ft_strncmp(str, limiter, ft_strlen(str)))
			break ;
		str = here_dollar(str);
		ft_putstr_fd(str, fd);
		free(str);
	}
	close(fd);
	if (str)
		free(str);
	free(limiter);
	free(filename);
	exit (0);
}

char	*get_ret(char *rd_line, int idx, int *i, int quote)
{
	int		j;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (idx + 2));
	ret[idx + 1] = 0;
	ret[idx] = '\n';
	j = 0;
	while (rd_line[*i] && !ft_isspace(rd_line[*i]) && !check_type(rd_line, *i))
	{
		if (rd_line[*i] == '\"' || rd_line[*i] == '\'')
		{
			add_quote(rd_line + *i, &ret, j, quote);
			*i += quote + 2;
			j += quote;
			continue ;
		}
		ret[j] = rd_line[*i];
		(*i)++;
		j++;
	}
	return (ret);
}

char	*check_limiter(char *rd_line, int *size)
{
	int		i;
	int		j;
	int		start;
	char	*ret;
	int		quote;

	start = 0;
	while (rd_line[start] && ft_isspace(rd_line[start]))
		start++;
	if (!rd_line[start] || check_type(rd_line, start))
		return (0);
	j = 0;
	i = start;
	j = lmt_size(rd_line, start, &quote);
	if (quote < 0)
		return (0);
	ret = get_ret(rd_line, j, &start, quote);
	*size += start + 1;
	return (ret);
}

int	here_utils(char *str, char *file)
{
	int	status;

	free(file);
	free(str);
	wait(&status);
	g_env->status = WEXITSTATUS(status);
	if (g_env->status == 130)
	{
		g_env->status = 1;
		return (0);
	}
	return (1);
}

int	set_heredoc(char *rd_line)
{
	int		i;
	int		size;
	pid_t	pid;
	char	*str;
	char	*file;

	i = -1;
	size = 0;
	signal(SIGINT, SIG_IGN);
	while (rd_line[++i])
	{
		if (!ft_strncmp(rd_line + i, "<<", 2))
		{
			str = check_limiter(rd_line + i + 2, &i);
			if (!str)
				return (1);
			pid = fork();
			file = get_filename(size++);
			if (pid == 0)
				set_heredoc_file(str, file);
			if (!here_utils(str, file))
				return (0);
		}
	}
	return (1);
}
