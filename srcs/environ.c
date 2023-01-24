/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:42:05 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/24 21:31:56 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*check_env(char	*str)
{
	t_env	*tmp;
	char	*key;
	int		i;

	i = 0;
	tmp = env;
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

void	make_env(void)
{
	int			i;

	if (!env)
	{
		env = (t_env*)malloc(sizeof(t_env));
		if (!env)
			print_error("allocated error", 1);
		env->key = get_key(environ[0]);
		env->val = get_val(environ[0]);
		env->next = NULL;
	}
	i = 0;
	while (environ[++i])
		add_back(environ[i]);
}

void	add_back(char *eviron)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	if (!tmp->next)
		print_error("allocated error", 1);
	tmp = tmp->next;
	tmp->key = get_key(eviron);
	tmp->val = get_val(eviron);
	tmp->next = NULL;
}
