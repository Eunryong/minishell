/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:21:30 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 19:40:51 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *str)
{
	char	*key;
	int		i;

	key = get_key(str);
	i = 0;
	while (key[++i])
	{
		if (!ft_isalnum(key[i]))
		{
			free(key);
			return (0);
		}
	}
	free(key);
	return (1);
}

int	check_str_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	make_shlvl(char *str)
{
	t_env	*tmp;
	char	*val;

	tmp = g_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	if (!tmp->next)
		print_error("allocated error", 1, 1);
	tmp = tmp->next;
	tmp->key = get_key(str);
	val = get_val(str);
	tmp->val = ft_itoa(ft_atoi(val) + 1);
	free(val);
	tmp->next = NULL;
}

void	add_quote(char *str, char **ret, int j, int quote)
{
	int	i;

	i = 1;
	while (i < quote + 1)
	{
		(*ret)[j] = str[i];
		i++;
		j++;
	}
}

int	lmt_size(char *rd_line, int i, int *quote)
{
	int	j;

	j = 0;
	while (rd_line[i] && !ft_isspace(rd_line[i]) && !check_type(rd_line, i))
	{
		if (rd_line[i] == '\"' || rd_line[i] == '\'')
		{
			*quote = check_quote(rd_line + i);
			i += *quote + 2;
			j += *quote;
			continue ;
		}
		i++;
		j++;
	}
	return (j);
}
