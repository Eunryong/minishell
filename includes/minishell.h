/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:11:36 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/21 18:43:02 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include "libft.h"
# include "structure.h"

typedef struct s_arg
{
	char			**env;
	char			**cmd;
	int				infile;
	int				outfile;
	struct s_arg	*next;
}	t_arg;

int		builtins_check(char *line, int status);
void	set_excute(char *line, char **envp);
void	print_error(char *str, int exit_code);
int		display_env(char *line);
int		add_env(char *line);
int		remove_env(char *line);
int		print_exit(int status);
#endif
