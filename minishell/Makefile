NAME			= minishell

SRCS			= $(wildcard srcs/*.c)

SRCS_OBJS		= $(SRCS:.c=.o)

CC				= gcc 
CFLAGS			= -Wall -Wextra -Werror -I ./includes
INCLUDE			=  -I ~/.brew/opt/readline/include 
LIBS			= -L ~/.brew/opt/readline/lib -lreadline
RM				= rm -f

all: $(NAME)

$(NAME): $(SRCS_OBJS)
	$(CC) $(LIBS) $(SRCS_OBJS) $(INCLUDE) -o $(NAME)

clean:
	$(RM) $(SRCS_OBJS)
	
fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all bonus clean fclean re