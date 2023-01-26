/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:11:36 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/26 18:40:44 by eunrlee          ###   ########.fr       */
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

int		builtins_check(t_line *line);
void	builtins_exec(t_line *line);
void	builtins_set(t_line *line, int flag);

void	get_pwd(void);
void	change_dir(t_line *line);
void	remove_env(t_env *del);
void	unset_env(t_line *line);
void	export_env(t_line *line);
void	print_exit(t_line *line);
void	print_export(void);
void	print_env(t_line *line);
t_env	*check_env(char *str);

int		wait_all(t_line *line, pid_t last_pid);

void	print_error(char *str, int exit_code);

char	**push_back_arr(char **env, char *str, int size);
void	add_back(char *eviron);
char	**env_to_arr(void);
char	*env_to_str(char *key, char *val);

char	*get_key(char *str);
char	*get_val(char *str);
void	make_env(void);
void	backup_fd(t_line *line);

char	**get_cmd_arg(t_line *line, int size);
char	*get_cmd(char **path, char *cmd);
void	set_excute(t_line *line);
void	get_io(t_line *line, int *fd, int i);
void	parse(t_line *line, char *rd_line, char **envp);
#endif
