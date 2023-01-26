/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:18:16 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/26 15:18:18 by eunrlee          ###   ########.fr       */
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

void	change_dir(t_line *line)
{
	int		result;
	t_env	*home;

	if (!line->cmd->next)
	{
		home = check_env("HOME");
		result = chdir(home->val);
	}
	else
		result = chdir(line->cmd->next->str);
	if (result == -1)
		perror(line->cmd->next->str);
}
