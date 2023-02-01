/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:10:35 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 13:20:50 by eunrlee          ###   ########.fr       */
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
		print_error("allocated error", 1, 1);
	ret[i] = 0;
	i = -1;
	while (ft_strncmp(env[++i], str, ft_strlen(str)))
		ret[i] = env[i];
	free (env[i]);
	while (env[++i + 1])
		ret[i] = env[i + 1];
	free(env);
	return (ret);
}

char	**push_back_arr(char **str_tmp, char *str, int size)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		print_error("allocated error", 1, 1);
	ret[size] = 0;
	i = -1;
	while (++i < size - 1)
		ret[i] = str_tmp[i];
	ret[i] = str;
	if (str_tmp)
		free(str_tmp);
	return (ret);
}

char	*env_to_str(char *key, char *val)
{
	char	*ret;
	int		k_len;
	int		v_len;
	int		i;

	k_len = ft_strlen(key);
	v_len = ft_strlen(val);
	ret = (char *)malloc(sizeof(char) * (k_len + v_len + 2));
	if (!ret)
		print_error("allocated error", 1, 1);
	i = -1;
	while (++i < k_len)
		ret[i] = key[i];
	ret[i] = '=';
	i = -1;
	while (++i < v_len)
		ret[k_len + i + 1] = val[i];
	ret[k_len + i + 1] = 0;
	return (ret);
}

char	**env_to_arr(void)
{
	char	**ret;
	t_env	*tmp;
	char	*str_tmp;
	int		size;

	ret = 0;
	tmp = g_env;
	size = 0;
	while (tmp)
	{
		if (tmp->val)
		{
			str_tmp = env_to_str(tmp->key, tmp->val);
			ret = push_back_arr(ret, str_tmp, ++size);
		}
		tmp = tmp->next;
	}
	return (ret);
}
