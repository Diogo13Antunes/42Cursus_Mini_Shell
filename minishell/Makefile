# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 10:55:19 by dsilveri          #+#    #+#              #
#    Updated: 2022/08/30 09:06:12 by dcandeia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= ./srcs/signal_handler.c							\
				  ./srcs/utils.c									\
				  ./srcs/tree/add_new_node.c						\
				  ./srcs/tree/tree.c								\
				  ./srcs/tree/free_tree.c							\
				  ./srcs/get_prompt.c								\
				  ./srcs/utils2.c									\
				  ./srcs/alloc_mem.c								\
				  ./srcs/env_vars/env_lst.c							\
				  ./srcs/env_vars/env_vars.c						\
				  ./srcs/env_vars/free_env_lst.c					\
				  ./srcs/minishell.c								\
				  ./srcs/exit_status.c								\
				  ./srcs/parser/syntax_error.c						\
				  ./srcs/parser/parser.c							\
				  ./srcs/parser/token_parser.c						\
				  ./srcs/parser/update_node.c						\
				  ./srcs/parser/utils_parser.c						\
				  ./srcs/parser/utils_parser2.c						\
				  ./srcs/parser/get_next_token.c					\
				  ./srcs/error_handler/error_handler.c				\
				  ./srcs/error_handler/print_error.c				\
				  ./srcs/error_handler/error_handler2.c				\
				  ./srcs/builtins/cmd_pwd.c							\
				  ./srcs/builtins/builtin_print_export.c			\
				  ./srcs/builtins/cmd_unset.c						\
				  ./srcs/builtins/cmd_env.c							\
				  ./srcs/builtins/cmd_echo.c						\
				  ./srcs/builtins/cmd_export.c						\
				  ./srcs/builtins/builtin_check_export_elements.c	\
				  ./srcs/builtins/cmd_exit.c						\
				  ./srcs/builtins/cmd_cd.c							\
				  ./srcs/executor/exec_builtins.c					\
				  ./srcs/executor/get_cmd_path.c					\
				  ./srcs/executor/executor.c						\
				  ./srcs/executor/utils_executor.c					\
				  ./srcs/executor/pipe.c							\
				  ./srcs/executor/hdoc.c							\
				  ./srcs/executor/file_redir.c						\
				  ./srcs/executor/wait_cmds.c

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
