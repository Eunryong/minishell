# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 22:01:20 by eunrlee           #+#    #+#              #
#    Updated: 2023/01/25 17:30:38 by eunrlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3
RL_LIB = -lreadline -L$(HOME)/.brew/opt/readline/lib
RL_INC = -I$(HOME)/.brew/opt/readline/include
NAME = minishell
LIBFT = ./libft/libft.a
SRCS = ./srcs/main.c ./srcs/env_ctl.c ./srcs/environ.c ./srcs/arr.c ./srcs/excute.c ./srcs/redirection.c ./srcs/ft_cmd.c ./srcs/parse.c ./srcs/builtins.c
OBJS = $(SRCS:.c=.o)
HEADER = -I./includes

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(HEADER) $(LIBFT) $(MFLAGS) $(OBJS) $(RL_LIB)
%.o : %.c
			$(CC) $(CFLAGS) $(RL_INC) $(HEADER) -c $< -o $@
$(LIBFT) :
		make -C ./libft bonus
clean :
		make -C ./libft fclean
		rm -rf $(OBJS)
