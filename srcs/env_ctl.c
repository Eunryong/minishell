/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:10:54 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/23 19:12:35 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *env;

void	add_back(char *eviron)
{
	t_env	*ret;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	if (!tmp->next)
		exit_error(amkldsf);
	tmp = tmp->next;
	tmp->ket = get_key(eviron);
	tmp->val = get_val(eviron);
	tmp->next = NULL;
}


void	export_env(t_line *line)
{
	if (!line->cmd->next)
		// ㅊㅜㄹ력
	else if (ft_strchr(line->cmd->next->str, '='))
		//치환
	else
		add_back(line->cmd->next->str);
}

void	make_env(void)
{
	extern char **eviron;
	t_env		tmp;
	
	if (!env)
	{
		env = (t_env*)malloc(sizeof(t_env));
		if (!env)
			exit_error(adjs);
		env->key = get_key(eviron[0]);
		env->val = get_val(eviron[0]);
		env->next = NULL;
	}
	i = 0;
	while (eviron[++i])
		add_back(eviron[i]);
}
