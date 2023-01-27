/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:11:36 by eunrlee           #+#    #+#             */
/*   Updated: 2023/01/27 13:29:16 by eunrlee          ###   ########.fr       */
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

int		builtins_check(char *str);
void	builtins_exec(char **cmd_arg);
void	builtins_set(t_line *line);

void	get_pwd(void);
void	change_dir(char **cmd_arg);
void	remove_env(t_env *del);
void	unset_env(char **cmd_arg);
void	export_env(char **cmd_arg);
void	print_exit(char **cmd_arg);
void	print_export(void);
void	print_env(char **cmd_arg);
t_env	*check_env(char *str);

int		wait_all(t_line *line, pid_t last_pid);

void	clear_cmd(t_line *line);

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

char	*get_filename(int i);
void	free_cmd(char **cmd_arg);
void	parse(t_line *line, char *rd_line, char **envp);
#endif
