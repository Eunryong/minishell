/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:10:54 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 16:29:46 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_env *del)
{
	t_env	*tmp;

	tmp = g_env;
	if (del == tmp)
	{
		g_env = g_env->next;
		free (del->key);
		if (del->val)
			free(del->val);
		free(del);
		return ;
	}
	tmp = g_env;
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free(del->key);
	if (del->val)
		free(del->val);
	free(del);
}

void	print_env(char **cmd_arg)
{
	t_env	*tmp;

	if (cmd_arg[1])
		return (print_error("Invalid argument.\n", 1, 0));
	tmp = g_env;
	while (tmp)
	{
		if (tmp->val)
			ft_printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

void	print_export(void)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		if (tmp->val)
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->val);
		else
			ft_printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	export_env(char	**cmd_arg)
{
	t_env	*env_tmp;
	int		i;

	if (!cmd_arg[1])
	{
		print_export();
		return ;
	}
	i = 0;
	while (cmd_arg[++i])
	{
		if (!ft_isalpha(cmd_arg[i][0]) || !check_key(cmd_arg[i]))
			syntax_error("not a valid identifier", 1, 0);
		else if (check_env(cmd_arg[i]) && ft_strchr(cmd_arg[i], '='))
		{
			env_tmp = check_env(cmd_arg[i]);
			if (env_tmp->val)
				free(env_tmp->val);
			env_tmp->val = get_val(cmd_arg[i]);
		}
		else if (!check_env(cmd_arg[i]))
			add_back(cmd_arg[i]);
	}
}

void	unset_env(char **cmd_arg)
{
	t_env	*env_tmp;
	int		i;

	i = 0;
	while (cmd_arg[++i])
	{
		if (!ft_isalpha(cmd_arg[i][0]) || !check_key(cmd_arg[i]))
			syntax_error("not a valid identifier", 1, 0);
		env_tmp = check_env(cmd_arg[i]);
		if (env_tmp)
			remove_env(env_tmp);
	}
}
