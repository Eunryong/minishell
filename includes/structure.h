/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:42:45 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/02 19:05:27 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum e_type
{
	cmd,
	red,
	pip
}	t_type;

typedef struct s_env
{
	char			*key;
	char			*val;
	int				status;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*str;
	int				type;
	int				quote;
	int				dollar;
	int				status;
	int				pipe;
	int				space;
	int				heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_line
{
	t_cmd	*cmd;
	int		size;
	char	**env;
	int		input;
	int		output;
	int		syntax;
}	t_line;

#endif
