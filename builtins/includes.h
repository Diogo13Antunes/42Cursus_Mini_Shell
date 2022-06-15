/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:35:37 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/15 10:04:05 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

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
# include "LIBFT_NEW/includes/libft.h"

# define FALSE 0
# define TRUE 1

/*================================ BUILTINS ==============================*/

int		builtin_pwd(int fd);
void	builtin_echo(char **matriz, int fd);
void	builtin_env(t_env firt_elem, int fd);
int		builtin_cd(char *path, t_env *env);
void	builtin_export(t_env *env, char **elems, int fd);
void	builtin_unset(t_env **env, const char *elem);

/*================================== UTILS ================================*/

void	print_export(t_env *env, int fd);
int		check_element(char *element);
t_env	*get_env_list(char **env);
t_env	*exist_env_elem(t_env *env, const char *elem_name);
int		find_char(char *str, char c);
t_env	*create_new_env_elem(char *var, char *cont);
t_env	*get_new_env_elem(char *env_str);
void	print_env(t_env	*env, int fd);
int		env_lst_size(t_env *env);
char	*create_full_env(char *var, char *cont);
int		check_oldpwd(t_env *env);
char	**get_env_matrix(t_env *list);
void	ft_update_elem(t_env *elem, char *element);

#endif
