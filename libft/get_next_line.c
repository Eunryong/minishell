/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 22:50:37 by eunrlee           #+#    #+#             */
/*   Updated: 2022/12/20 15:07:24 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sub_line(t_node *fd_lst, t_node **head)
{
	size_t	i;
	char	*temp;
	char	*ret;

	i = 0;
	temp = fd_lst -> backup;
	while (temp[i] != '\n')
		i++;
	ret = ft_substr(temp, 0, i + 1);
	if (!ret)
		return (free_node(fd_lst, head));
	if (!temp[i + 1] && fd_lst -> size == 0)
		free_node(fd_lst, head);
	else
	{
		fd_lst -> backup = ft_strdup(temp + i + 1);
		free(temp);
		if (!fd_lst -> backup)
		{
			free(ret);
			return (free_node(fd_lst, head));
		}
	}
	return (ret);
}	

static char	*get_line(int fd, t_node *fd_lst, t_node **head)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	char	*temp;

	while (!ft_strchr(fd_lst -> backup, '\n') && fd_lst -> size)
	{
		temp = fd_lst -> backup;
		fd_lst -> size = read(fd, buffer, BUFFER_SIZE);
		if (fd_lst -> size == -1)
			return (free_node(fd_lst, head));
		buffer[fd_lst ->size] = '\0';
		fd_lst -> backup = ft_strjoin(fd_lst -> backup, buffer);
		free(temp);
		if (!fd_lst -> backup)
			return (free_node(fd_lst, head));
	}
	if (ft_strchr(fd_lst -> backup, '\n'))
		return (sub_line(fd_lst, head));
	if (!(fd_lst -> backup)[0])
		return (free_node(fd_lst, head));
	line = ft_strdup(fd_lst -> backup);
	if (!line)
		return (free_node(fd_lst, head));
	free_node(fd_lst, head);
	return (line);
}

static t_node	*new_list(int fd)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (0);
	new -> fd = fd;
	new -> backup = ft_strdup("");
	if (!new -> backup)
	{
		free(new);
		new = NULL;
		return (0);
	}
	new -> size = 1;
	new -> next = NULL;
	return (new);
}

static t_node	*find_fd(t_node **head, int fd)
{
	t_node	*ret;

	ret = (*head);
	if (!(*head))
	{
		(*head) = new_list(fd);
		if (!(*head))
			return (0);
		return ((*head));
	}
	while (ret)
	{
		if (ret -> fd == fd)
			break ;
		if (ret -> next == NULL)
		{
			ret -> next = new_list(fd);
			if (!ret -> next)
				return (0);
		}
		ret = ret -> next;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*fd_lst;
	char			*result;

	if (BUFFER_SIZE <= 0)
		return (0);
	fd_lst = find_fd(&head, fd);
	if (!fd_lst)
		return (0);
	result = get_line(fd, fd_lst, &head);
	if (!result)
		return (0);
	return (result);
}
