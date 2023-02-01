# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 14:00:40 by eunrlee           #+#    #+#              #
#    Updated: 2023/01/31 06:58:15 by wocheon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a
SRCS = ft_isalpha.c ft_isalnum.c ft_isprint.c ft_atoi.c ft_isdigit.c \
	   ft_isascii.c ft_bzero.c ft_memset.c ft_memcmp.c ft_memcpy.c \
	   ft_memmove.c ft_memchr.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
	   ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlen.c \
	   ft_calloc.c ft_strdup.c ft_strnstr.c ft_strjoin.c ft_substr.c \
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_printf.c ft_printmem.c ft_printnum.c ft_printchar.c get_next_line.c\
	   get_next_line_utils.c ft_isspace.c ft_strcmp.c
OBJS = $(SRCS:.c=.o)
AR = ar
CC = cc
CFLAGS = -Wall -Wextra -Werror
B_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		 ft_lstdelone.c ft_lstiter.c ft_lstadd_back.c ft_lstclear.c ft_lstmap.c
B_OBJS = $(B_SRCS:.c=.o)
HEADER = -I../includes

all	: $(NAME)

$(NAME) : $(OBJS)
	$(AR) -crs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

bonus : $(B_OBJS)
	@make OBJS="$(OBJS) $(B_OBJS)" all

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
