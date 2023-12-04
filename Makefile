# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 22:01:20 by eunrlee           #+#    #+#              #
#    Updated: 2023/02/02 18:21:39 by wocheon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra #-g
RL_LIB = -lreadline -L/opt/homebrew/opt/readline/lib
RL_INC = -I/opt/homebrew/opt/readline/include
NAME = minishell
LIBFT = ./libft/libft.a
SRCS = ./srcs/main.c \
	./srcs/execute/env_ctl.c ./srcs/execute/environ.c ./srcs/execute/execute.c \
	./srcs/execute/redirection.c ./srcs/execute/builtins.c ./srcs/execute/dir.c \
	./srcs/execute/heredoc.c ./srcs/execute/heredoc_utils.c \
	./srcs/parse/parse.c ./srcs/parse/check.c ./srcs/parse/seperate_quote.c ./srcs/parse/dollar.c \
	./srcs/parse/seperate_type.c ./srcs/parse/seperate_space.c \
	./srcs/utils/check_str.c ./srcs/utils/signal.c ./srcs/utils/list.c \
	./srcs/utils/arr.c ./srcs/utils/ft_cmd.c ./srcs/utils/free.c ./srcs/utils/error.c
OBJS = $(SRCS:.c=.o)
HEADER = -I./includes

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(HEADER) $(LIBFT) $(OBJS) $(RL_LIB)
%.o : %.c
			$(CC) $(CFLAGS) $(RL_INC) $(HEADER) -c $< -o $@
$(LIBFT) :
		make -C ./libft bonus
clean :
		make -C ./libft fclean
		rm -rf $(OBJS)
fclean : clean
		rm -rf $(NAME)
re :
		make fclean
		make all
		
