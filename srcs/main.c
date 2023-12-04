/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:28:38 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/02 18:20:44 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (0);
		line++;
	}
	return (1);
}

void	main_init(int argc, char **argv, char **envp, t_line *line)
{
	struct termios	term;

	(void)argv;
	if (argc != 1)
		print_error("argument input error", 126, 1);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	make_env(envp);
	line->input = dup(STDIN_FILENO);
	line->output = dup(STDOUT_FILENO);
}

void	exit_bus(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

int	input_rd(t_line line, char *rd_line)
{
	t_cmd	*new;

	if (!set_heredoc(rd_line))
		return (0);
	sig_init();
	if (!parse(&line, rd_line))
		return (0);
	new = line.cmd;
	while (new)
	{
		if (new->type == pip)
			line.size++;
		new = new->next;
	}
	if (line.syntax || set_execute(&line) == -2)
	{
		g_env->status = 1;
		clear_cmd(&line);
		return (0);
	}
	clear_cmd(&line);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char			*rd_line;
	struct termios	term;
	t_line			line;

	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv, envp, &line);
	while (1)
	{
		sig_init();
		rd_line = readline("BUSshell $ ");
		if (!rd_line)
			exit_bus();
		if (*rd_line != '\0')
			add_history(rd_line);
		if (*rd_line != '\0' && !is_space(rd_line))
		{
			if (!input_rd(line, rd_line))
			{
				free(rd_line);
				continue ;
			}
		}
		free(rd_line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
