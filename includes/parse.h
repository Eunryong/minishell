/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:19:12 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/01 14:47:56 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structure.h"
//parse.c
int		parse(t_line *line, char *rd_line);

//list.c
t_cmd	*new_cmd(void);
t_cmd	*push_back(t_line *line);
void	remove_cmd(t_line *line, t_cmd **cmd);
t_cmd	*seperate_cmd(t_cmd **cmd);

//seperate_quote.c
int		double_quote(t_line *line, char *rd_line);
int		small_quote(t_line *line, char *rd_line);
int		get_arg(t_line *line, char *rd_line);
void	seperate_quote(t_line *line, char *rd_line);

//check.c
int		quote_check(char *rd_line);
void	check_dollar(t_line *line);
int		check_type(char *str, int i);
int		check_error(t_line *line);
int		check_quote(char *str);
//dollar.c
char	*change_dollar(char *str, int dollar);
char	*trans_status(char *str, int *i);
char	*trans_dollar(char *str, int *i);
int		is_dollar(char *str);

//seperate_type.c
void	seperate_as_type(t_line *line);
void	seperate_type(t_cmd **cmd, char *str, int size, int i);

//seperate_space.c
void	seperate_space(t_line *line);
int		check_space(char *str);
void	before_split(t_line *line, t_cmd **cmd, char *str);
void	split_cmd(t_cmd **cmd, char *str);

#endif
