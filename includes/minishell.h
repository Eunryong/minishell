/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:11:36 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/24 22:26:43 by eunrlee          ###   ########.fr       */
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

extern t_env *env;

extern char **environ;

int		builtins_check(t_line *line, int status);
void	set_excute(t_line *line);

void	print_error(char *str, int exit_code);

char	**push_back_arr(char **env, char *str, int size);
void	add_back(char *eviron);
char	**env_to_arr(void);
char	*env_to_str(char *key, char *val);

void	remove_env(t_env *del);
int		unset_env(t_line *line);
int		export_env(t_line *line);
int		print_exit(t_line *line);
void	print_export(void);
int		print_env(void);
t_env	*check_env(char *str);
char	*get_key(char *str);
char	*get_val(char *str);
void	make_env(void);

char	**get_cmd_arg(t_line *line);
char	*get_cmd(char **path, char *cmd);
void	get_io(t_line *line, int *fd, int i);
void	parse(t_line *line, char *rd_line, char **envp);
#endif
