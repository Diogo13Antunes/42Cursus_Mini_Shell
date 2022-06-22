/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:15:03 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/22 14:55:16 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_user(t_env *user_nd);
static char *get_dir(t_env *dir_nd);

char *get_prompt_str(t_env *env)
{
	char	*prompt;
	int		prompt_size;
	char	*user;
	char	*dir;

	user = get_user(exist_env_elem(env, "USER"));
	dir = get_dir(exist_env_elem(env, "PWD"));
	prompt_size = ft_strlen(user) + ft_strlen(dir) + 1;
	prompt = ft_calloc(prompt_size, sizeof(char));
	ft_strcat(prompt, user);
	ft_strcat(prompt, dir);
	free (user);
	free(dir);
	return (prompt);
}

static char *get_user(t_env *user_nd)
{
	char	*user;
	int		user_size;
	
	user_size = ft_strlen(user_nd->content);
	user_size += ft_strlen(BRED) + ft_strlen(RESET) + 4;
	user = ft_calloc(user_size, sizeof(char));
	ft_strcat(user, "[");
	ft_strcat(user, BRED);
	ft_strcat(user, user_nd->content);
	ft_strcat(user, RESET);
	ft_strcat(user, "]");
	ft_strcat(user, " ");
	return (user);
}

static char *get_dir(t_env *dir_nd)
{
	char	*dir;
	int		dir_size;
	char 	*dir_name;
	
	dir_name = ft_strrchr(dir_nd->content, '/') + 1;
	dir_size = ft_strlen(dir_name);
	dir_size += ft_strlen(BGRN) + ft_strlen(RESET) + 4;

	dir = ft_calloc(dir_size, sizeof(char));
	ft_strcat(dir, BGRN);
	ft_strcat(dir, dir_name);
	ft_strcat(dir, RESET);
	ft_strcat(dir, " > ");
	return (dir);
}


