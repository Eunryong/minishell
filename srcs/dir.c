/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:18:16 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/27 14:19:05 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
}

void	change_dir(char **arg_cmd)
{
	int		result;
	t_env	*home;

	if (!arg_cmd[1])
	{
		home = check_env("HOME");
		result = chdir(home->val);
	}
	else
		result = chdir(arg_cmd[1]);
	ft_printf("%s\n", arg_cmd[1]);
	if (result == -1)
		perror(arg_cmd[1]);
}
