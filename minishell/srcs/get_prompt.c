/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:15:03 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/25 19:05:19 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user(t_env *user_nd);
static char	*get_dir(t_env *dir_nd, t_env *env);

char	*get_prompt_str(t_env *env)
{
	int		prompt_size;
	char	*prompt;
	char	*user;
	char	*dir;

	user = get_user(exist_env_elem(env, "USER"));
	dir = get_dir(exist_env_elem(env, "PWD"), env);
	prompt_size = ft_strlen(user) + ft_strlen(dir) + 1;
	prompt = ft_calloc(prompt_size, sizeof(char));
	ft_strcat(prompt, user);
	ft_strcat(prompt, dir);
	free (user);
	free(dir);
	return (prompt);
}

static char	*get_user(t_env *user_nd)
{
	int		user_size;
	char	*user;

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

static char	*get_dir(t_env *dir_nd, t_env *env)
{
	int		dir_size;
	char	*dir_name;
	char	*home_path;
	char	*dir;

	home_path = exist_env_elem(env, "HOME")->content;
	if (ft_strlen(dir_nd->content) > 1)
		dir_name = ft_strrchr(dir_nd->content, '/') + 1;
	else
		dir_name = dir_nd->content;
	dir_size = ft_strlen(dir_name);
	dir_size += ft_strlen(BGRN) + ft_strlen(RESET) + 4;
	dir = ft_calloc(dir_size, sizeof(char));
	ft_strcat(dir, BGRN);
	if (!ft_strcmp(home_path, dir_nd->content))
		ft_strcat(dir, "~");
	else
		ft_strcat(dir, dir_name);
	ft_strcat(dir, RESET);
	ft_strcat(dir, " > ");
	return (dir);
}
