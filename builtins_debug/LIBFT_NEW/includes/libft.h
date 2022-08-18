/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:27:05 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/15 09:48:58 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <stdio.h>
# include <fcntl.h>
# include <term.h>

typedef struct s_env
{
	char			*variable;
	char			*content;
	char			*full;
	struct s_env	*next;
}				t_env;

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
t_env	*ft_lstnew(char *variable, char *content, char *full);
int		ft_lstsize(t_env *lst);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstdelone(t_env *lst);
void	ft_lstclear(t_env **lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlcat(char *dst, const char *src, int destsize);
void	ft_bzero(void *s, int tam);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *s, int c, size_t len);
char	*ft_substr(char const *s, int start, int len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_strchr(const char *str, int c);
// int		ft_isdigit(int c);
// int		ft_isascii(int c);
// int		ft_isprint(int c);
// void	*ft_memcpy(void *dest, const void *src, size_t n);
// void	*ft_memmove(void *dest, const void *src, size_t n);
// int		ft_toupper(int c);
// int		ft_tolower(int c);
// char	*ft_strrchr(const char *str, int c);
// void	*ft_memchr(const void *str, int c, size_t n);
// int		ft_memcmp(const void *s1, const void *s2, size_t n);
// char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
// int		ft_atoi(const char *str);
// char	*ft_strdup(const char *s1);
// void	ft_putchar_fd(char c, int fd);
// void	ft_putendl_fd(char *s, int fd);
// void	ft_putnbr_fd(int n, int fd);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strtrim(char const *s1, char const *set);
// char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
// char	*ft_striteri(char *s, void (*f)(unsigned int, char *));
// char	*ft_itoa(int n);
// char	**ft_split(char const *s, char c);
// void	ft_lstiter(t_list *lst, void (*f)(void *));
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
