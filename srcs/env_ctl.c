/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:10:54 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/22 16:06:29 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env(char **env, char *str)
{
	int		i;
	char	tmp;
	int		flag;

	i = 0;
	tmp = str;
	flag = 0;
	if (ft_strchr(tmp, '='))
	{
		flag = 1;
		while (tmp[i] != '=')
			i++;
		tmp = ft_substr(str, 0, i);
	}
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)))
			return (1);
	}
	if (flag)
		free(tmp);
	return (0);
}

int	display_env(t_line *line)
{
	int	i;

	i = -1;
	while (line->env[++i])
		ft_printf("%s\n", line->env[i]);
	return (1);
}

int	add_env(t_line *line)
{
	t_cmd	*tmp;

	tmp = line->cmd->next;
	if (!tmp)
		return (display_env(line));
	while (tmp)
	{
		if (check_env(line->env, tmp->str) && ft_strchr(tmp->str, '='))
			line->env = change_env(line->env, tmp->str)
		else if (ft_strchr(tmp->str, '='))
			line->env = add_back(line->env, tmp->str);
		tmp = tmp->next;
	}	
	return (1);
}

int	remove_env(t_line *line) // unset
{
	t_cmd	*tmp;

	tmp = line->cmd->next;
	while (tmp)
	{
		if (check_env(line->env, tmp->str))
			line->env = remove_arr(line->env, str);
		tmp = tmp->next;
	}
	return (1);
}

int	print_exit(t_line *line)
{
	ft_printf("%d\n", line->status >> 8);
	return (1);
}
