/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:11:36 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/02 00:58:58 by eunrlee          ###   ########.fr       */
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
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"
# include "structure.h"
# include "parse.h"

t_env	*g_env;

int		is_space(char *line);
int		builtins_check(char *str);
void	builtins_exec(char **cmd_arg, int size);
int		builtins_set(t_line *line);
int		lmt_size(char *rd_line, int i, int *quote);

void	add_quote(char *rd_line, char **ret, int j, int quote);
void	get_pwd(void);
void	change_dir(char **cmd_arg);
void	remove_env(t_env *del);
void	unset_env(char **cmd_arg);
void	export_env(char **cmd_arg);
int		check_key(char *str);
void	print_export(void);
void	print_env(char **cmd_arg);
t_env	*check_env(char *str);
void	make_shlvl(char *str);

int		wait_all(pid_t last_pid);
char	*here_dollar(char *str);
void	clear_cmd(t_line *line);

void	print_error(char *str, int exit_code, int flag);
void	such_error(char **str, int exit_code, int flag);
void	cmd_error(char *str, int exit_code, int flag);
void	syntax_error(char *str, int exit_code, int flag);

char	**push_back_arr(char **env, char *str, int size);
void	add_back(char *eviron);
char	**env_to_arr(void);
char	*env_to_str(char *key, char *val);

char	*get_key(char *str);
char	*get_val(char *str);
void	make_env(char **environ);
void	backup_fd(t_line *line);

char	**get_cmd_arg(t_line *line, int size);
char	*get_cmd(char **path, char *cmd);
int		set_execute(t_line *line);
void	get_io(t_line *line, int *fd, int i);
t_cmd	*get_pipe(t_line *line, int size);

char	*get_filename(int i);
int		set_heredoc(char *line);
void	free_cmd(char **cmd_arg);

void	sig_init(void);
void	sig_exit(int signum);
int		check_str_n(char *str);

void	exit_shell(char	**cmd_arg, int size);
void	free_str(char *s1, char *s2, char *s3);

#endif
