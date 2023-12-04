/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:18:16 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 19:37:02 by wocheon          ###   ########.fr       */
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

void	check_dir(char **arg_cmd)
{
	int		result;
	t_env	*home;

	if (!arg_cmd[1])
	{
		home = check_env("HOME");
		if (home)
			result = chdir(home->val);
		else
			syntax_error("Home not set", 1, 0);
	}
	else
	{
		result = chdir(arg_cmd[1]);
		if (result == -1)
			print_error(arg_cmd[0], 1, 0);
	}
}

void	change_dir(char **arg_cmd)
{
	t_env	*old;
	char	*str;
	char	*tmp;

	check_dir(arg_cmd);
	tmp = getcwd(NULL, 0);
	old = check_env("OLDPWD");
	if (old)
	{
		free(old->val);
		old->val = tmp;
	}
	else
	{
		str = ft_strjoin("OLDPWD=", tmp);
		add_back(str);
		free(str);
		free(tmp);
	}
}

char	*get_filename(int i)
{
	char	*ret;
	char	*num;

	num = ft_itoa(i);
	ret = ft_strjoin("/tmp/.heredoc/", num);
	free(num);
	return (ret);
}
