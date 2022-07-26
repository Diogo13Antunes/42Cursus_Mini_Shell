# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 10:55:19 by dsilveri          #+#    #+#              #
#    Updated: 2022/07/26 14:58:01 by dsilveri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= $(wildcard srcs/*.c) \
				  $(wildcard srcs/builtins/*.c) \
				  $(wildcard srcs/parser/*.c) \
				  $(wildcard srcs/executor/*.c) \
				  $(wildcard srcs/tree/*.c)

LIBFT			= libft/libft.a

SRCS_OBJS		= $(SRCS:.c=.o)

CC				= gcc 
#CFLAGS			= -Wall -Wextra -Werror -I ./includes
CFLAGS			= -I ./includes
LIBS			= -lreadline
RM				= rm -f

MAKE_LIBFT		= make bonus -C libft/
CLEAN_LIBFT		= make clean -C libft/
FCLEAN_LIBFT	= make fclean -C libft/


all: $(NAME)

$(NAME): $(SRCS_OBJS)
	$(MAKE_LIBFT)
	$(CC) $(SRCS_OBJS) $(LIBFT) -o $(NAME) $(LIBS)

clean:
	$(CLEAN_LIBFT)
	$(RM) $(SRCS_OBJS)
	
fclean: clean
	$(FCLEAN_LIBFT)
	$(RM) $(NAME)

r: all
	clear && ./minishell

re:	fclean all

.PHONY: all bonus clean fclean re