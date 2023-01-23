/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:11:36 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/23 17:05:45 by eunrlee          ###   ########.fr       */
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
void	set_excute(t_line *line);
void	print_error(char *str, int exit_code);
int		display_env(char **env);
char	**add_back(char **env, char *str, int size);
char	**change_env(char **env, char *str);
char	**remove_arr(char **env, char *str);
int		remove_env(t_line *line);
int		print_exit(t_line *line);
int		print_export(char **env);
#endif
