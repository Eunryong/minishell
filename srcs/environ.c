/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:42:05 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/31 19:25:50 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*check_env(char	*str)
{
	t_env	*tmp;
	char	*key;
	int		i;

	i = 0;
	tmp = g_env;
	while (str[i] && str[i] != '=')
		i++;
	while (tmp)
	{
		key = tmp->key;
		if (!ft_strncmp(key, str, i))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

char	*get_key(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_val(char *str)
{
	int		i;

	if (!ft_strchr(str, '='))
		return (0);
	i = 0;
	while (str[i] != '=')
		i++;
	return (ft_strdup(str + i + 1));
}

void	make_env(char **environ)
{
	int	i;

	if (!g_env)
	{
		g_env = (t_env *)malloc(sizeof(t_env));
		if (!g_env)
			print_error("allocated error", 1, 1);
		g_env->key = get_key(environ[0]);
		g_env->val = get_val(environ[0]);
		g_env->next = NULL;
	}
	i = 0;
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], "SHLVL=", 6))
			make_shlvl(environ[i]);
		else
			add_back(environ[i]);
	}
}

void	add_back(char *str)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	if (!tmp->next)
		print_error("allocated error", 1, 1);
	tmp = tmp->next;
	tmp->key = get_key(str);
	tmp->val = get_val(str);
	tmp->next = NULL;
}
