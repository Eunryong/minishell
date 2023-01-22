/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:10:35 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/22 15:32:37 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_arr(char **env, char *str)
{
	int		i;
	char	**ret;
	i = 0;
	while (env[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * i);
	if (!ret)
		print_error("allocated error", 1);
	ret[i] = 0;
	i = -1;
	while (ft_strncmp(env[++i], str, ft_strlen(str)))
		ret[i] = env[i];
	free (env[i]);
	while (env[++i + 1])
	{
		ret[i] = env[i + 1];
	}
	free(env);
	return (ret);
}

char	**change_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], str, ft_strlen(str)))
		i++;
	free(env[i]);
	env[i] = ft_strdup(str);
	return (env);
}

char	**add_back(char **str_tmp, char *str, int size)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * size + 1);
	if (!ret)
		print_error("allocated error", 1);
	ret[size] = 0;
	i = -1;
	while (++i < size - 1)
		ret[i] = str_tmp[i];
	ret[i] = ft_strdup(str);
	if (str_tmp)
		free(str_tmp);
	return (ret);
}
