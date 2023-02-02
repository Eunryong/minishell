/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:35:47 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/02 19:35:57 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_dollar(char *str)
{
	int		size;
	int		i;
	char	*ret;

	i = 0;
	size = is_dollar(str);
	if (size == 0)
		return (str);
	ret = change_dollar(str, size);
	return (ret);
}
