/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:10:54 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/25 17:06:31 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_env *del)
{
	t_env	*tmp;

	tmp = env;
	if (del == tmp)
	{
		env = env->next;
		free (del->key);
		if (del->val)
			free(del->val);
		free(del);
		return ;
	}
	while (tmp->next == del)
		tmp = tmp->next;
	tmp->next = del->next;
	free(del->key);
	if (del->val)
		free(del->val);
	free(del);
}

int	print_env(void)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->val)
			ft_printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (1);
}

void	print_export(void)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->val)
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->val);
		else
			ft_printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

int	export_env(t_line *line)
{
	t_cmd	*tmp;
	t_env	*env_tmp;

	tmp = line->cmd->next;
	if (!tmp)
		print_export();
	while (tmp)
	{
		if (!ft_isalpha(tmp->str[0]))
			print_error("not a valid identifier", 1);
		else if (check_env(tmp->str) && ft_strchr(tmp->str, '='))
		{
			env_tmp = check_env(tmp->str);
			if (env_tmp->val)
				free(env_tmp->val);
			env_tmp->val = get_val(tmp->str);
		}
		else if (!check_env(tmp->str))
			add_back(tmp->str);
		tmp = tmp->next;
	}
	return (1);
}

int	unset_env(t_line *line)
{
	t_cmd	*tmp;
	t_env	*env_tmp;

	tmp = line->cmd->next;
	while (tmp)
	{
		env_tmp = check_env(tmp->str);
		if (env_tmp)
			remove_env(env_tmp);
		tmp = tmp->next;
	}
	return (1);
}
