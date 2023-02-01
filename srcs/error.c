/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:16:45 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/01 12:12:02 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *str, int exit_code, int flag)
{
	ft_putstr_fd("BUSshell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	if (!flag)
		g_env->status = exit_code;
	if (flag)
		exit(exit_code);
}

void	print_error(char *str, int exit_code, int flag)
{
	ft_putstr_fd("BUSshell: ", 2);
	perror(str);
	if (!flag)
		g_env->status = exit_code;
	if (flag)
		exit(exit_code);
}

void	cmd_error(char *str, int exit_code, int flag)
{
	ft_putstr_fd("BUSshell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (!flag)
		g_env->status = exit_code;
	if (flag)
		exit(exit_code);
}
