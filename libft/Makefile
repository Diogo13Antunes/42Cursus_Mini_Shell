# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:34:51 by dsilveri          #+#    #+#              #
#    Updated: 2022/06/23 14:43:20 by dcandeia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a

SRCS 	= ft_isalpha.c \
	  	  ft_isdigit.c \
	  	  ft_isalnum.c \
	  	  ft_isascii.c \
	  	  ft_isprint.c \
	  	  ft_strlen.c \
	   	  ft_memset.c \
	  	  ft_bzero.c \
	  	  ft_memcpy.c \
	  	  ft_memmove.c \
	  	  ft_strlcpy.c \
	  	  ft_strlcat.c \
	  	  ft_toupper.c \
	  	  ft_tolower.c \
		  ft_strchr.c \
	  	  ft_strrchr.c \
	  	  ft_strncmp.c \
	  	  ft_memchr.c \
	  	  ft_memcmp.c \
	  	  ft_strnstr.c \
	  	  ft_atoi.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_striteri.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_strcmp.c \
		  ft_strcat.c

OBJS		= $(SRCS:.c=.o)

BONUS_SRCS = ft_lstnew.c \
			 ft_lstadd_front.c \
			 ft_lstsize.c \
			 ft_lstlast.c \
			 ft_lstadd_back.c \
			 ft_lstdelone.c \
			 ft_lstclear.c \
			 ft_lstiter.c \
			 ft_lstmap.c

BONUS_OBJS 	= $(BONUS_SRCS:.c=.o)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I.
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJS) 
	   ar rc $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all