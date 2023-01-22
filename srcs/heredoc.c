/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:55:31 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/22 17:37:05 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_heredoc_file(char *limiter, char *filename)
{
	char	*str;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error("open error", 1);
	while (1)
	{
		str = get_next_line(0);
		if (!ft_strncmp(str, limiter, ft_strlen(str)))
			break ;
		ft_putstr(str, fd);
		free(str);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	free(limiter);
	free(filename);
	return (0);
}

int	set_heredoc(t_line *line)
{
	t_cmd	*tmp;
	int		i;
	pid_t	pid;

	tmp = line->cmd;
	i = 0;
	while (tmp)
	{
		if (cmd->type == red && !ft_strncmp(tmp->str, "<<", ft_strlen(tmp->str)))
		{
			tmp = tmp->next;
			pid = fork();
			if (pid == 0)
				set_heredoc_file(ft_strjoin(tmp->str, "\n"), \
						ft_strjoin("/tmp/.heredoc/", ft_itoa(i++)));
		}
		tmp = tmp->next;
	}
	wait_all(line, pid);
}
