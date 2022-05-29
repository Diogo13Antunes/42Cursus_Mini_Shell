# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 10:55:19 by dsilveri          #+#    #+#              #
#    Updated: 2022/05/29 18:42:27 by dsilveri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= $(wildcard srcs/*.c)
LIBFT			= libft/libft.a

SRCS_OBJS		= $(SRCS:.c=.o)

CC				= gcc 
CFLAGS			= -Wall -Wextra -Werror -I ./includes
INCLUDE			= -I ~/.brew/opt/readline/include 
LIBS			= -L ~/.brew/opt/readline/lib -lreadline
RM				= rm -f

MAKE_LIBFT		= make bonus -C libft/
CLEAN_LIBFT		= make clean -C libft/
FCLEAN_LIBFT	= make fclean -C libft/

all: $(NAME)

$(NAME): $(SRCS_OBJS)
	$(MAKE_LIBFT)
	$(CC) $(LIBS) $(SRCS_OBJS) $(INCLUDE) $(LIBFT) -o $(NAME)

clean:
	$(CLEAN_LIBFT)
	$(RM) $(SRCS_OBJS)
	
fclean: clean
	$(FCLEAN_LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY: all bonus clean fclean re