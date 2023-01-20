/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 22:51:57 by eunrlee           #+#    #+#             */
/*   Updated: 2022/12/20 15:07:04 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_node(t_node *fd_lst, t_node **head)
{
	t_node	*temp;
	t_node	*prev;

	temp = (*head);
	prev = NULL;
	while (temp != fd_lst)
	{
		prev = temp;
		temp = temp -> next;
	}
	if (!prev)
		(*head) = (*head)-> next;
	else
		prev -> next = temp -> next;
	free(fd_lst -> backup);
	free(fd_lst);
	fd_lst = NULL;
	return (0);
}
