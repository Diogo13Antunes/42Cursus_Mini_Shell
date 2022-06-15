# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:29:35 by dcandeia          #+#    #+#              #
#    Updated: 2022/06/15 09:48:26 by dcandeia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
ARRC = ar rc
CFLAGS = -Wall -Werror -Wextra -Imlx -g
RM = rm -rf

$(VERBOSE).SILENT:

HEADER = libft.h

INC = -I ./includes

SRC_PATH = ./sources

OBJ_PATH = ./objects

SRC_NAME = 	ft_strlcpy.c		\
			ft_putstr_fd.c		\
			ft_bzero.c			\
			ft_strcmp.c			\
			ft_isalpha.c		\
			ft_isalnum.c		\
			ft_strchr.c			\
			ft_strlcat.c		\
			ft_memset.c			\
			ft_substr.c			\
			ft_calloc.c			\
			ft_strlen.c			\
			ft_strncmp.c		\
			ft_lstnew.c			\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstclear.c		\
			ft_lstdelone.c		\
			ft_lstadd_front.c	\
			ft_lstadd_back.c

OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

all: $(NAME)

$(NAME) : $(OBJS)
	make norminette
	$(ARRC) $(NAME) $(OBJS)
	echo "\x1b[36m[LIBFT COMPILED]\x1b[0m"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p objects
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

norminette:
	clear
	echo "\x1b[33m[NORMINETTE]\x1b[0m"
	norminette | egrep -B1 'Error|Warning' | sed ''/Error/s//$(printf "\033[31m\033[4mError\033[0m")/'' | sed ''/Warning/s//$(printf "\033[33m\033[4mWarning\033[0m")/''

clean:
	$(RM) $(OBJ_PATH)
	echo "\033[33mall $(NAME).o files are removed\033[0m"

fclean: clean
	$(RM) $(NAME)
	echo "\033[31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re norminette