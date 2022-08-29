# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 10:55:19 by dsilveri          #+#    #+#              #
#    Updated: 2022/08/29 15:41:04 by dcandeia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= $(wildcard srcs/*.c) \
				  $(wildcard srcs/builtins/*.c) \
				  $(wildcard srcs/parser/*.c) \
				  $(wildcard srcs/executor/*.c) \
				  $(wildcard srcs/tree/*.c) \
				  $(wildcard srcs/error_handler/*.c) \
				  $(wildcard srcs/env_vars/*.c)

LIBFT			= libft/libft.a

SRCS_OBJS		= $(SRCS:.c=.o)

CC				= gcc 
#CFLAGS			= -Wall -Wextra -Werror -fsanitize=address -I ./includes
CFLAGS			= -g -I ./includes
LIBS			= -lreadline
RM				= rm -f

MAKE_LIBFT		= make bonus -C libft/
CLEAN_LIBFT		= make clean -C libft/
FCLEAN_LIBFT	= make fclean -C libft/

all: $(NAME)

$(NAME): $(SRCS_OBJS)
	$(MAKE_LIBFT)
	$(CC) $(CFLAGS) $(SRCS_OBJS) $(LIBFT) -o $(NAME) $(LIBS) 

norminette:
	clear
	@./norm.sh

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
