/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:10:54 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/27 13:20:51 by eunrlee          ###   ########.fr       */
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

void	print_env(char **cmd_arg)
{
	t_env	*tmp;

	if (cmd_arg[1])
		return (ft_putstr_fd("Invalid argument.\n", 2));
	tmp = env;
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

void	export_env(char	**cmd_arg)
{
	t_env	*env_tmp;
	int		i;

	if (!cmd_arg[1])
		print_export();
	i = 0;
	while (cmd_arg[++i])
	{
		if (!ft_isalpha(cmd_arg[i][0]))
			print_error("not a valid identifier", 1);
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
		env_tmp = check_env(cmd_arg[i]);
		if (env_tmp)
			remove_env(env_tmp);
	}
}
