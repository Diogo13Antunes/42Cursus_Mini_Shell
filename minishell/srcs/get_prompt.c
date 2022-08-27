/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:15:03 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/27 10:23:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user(t_env *user_nd);
static char	*get_dir(t_env *dir_nd, t_env *env);
static char	*create_prompt(t_env *env);
static void	clean_strs(char *s1, char *s2);

char	*get_prompt_str(t_env *env)
{
	int		prompt_size;
	char	*prompt;
	char	*user;
	char	*dir;

	prompt = create_prompt(env);
	if (!prompt)
	{
		prompt = oom_guard(ft_calloc(11, sizeof(char)));
		ft_strcat(prompt, "minish > ");
		return (prompt);
	}
	else
		return (prompt);
}

static char	*get_user(t_env *user_nd)
{
	int		user_size;
	char	*user;

	if (!user_nd)
		return (NULL);
	user_size = ft_strlen(user_nd->content);
	user_size += ft_strlen(BRED) + ft_strlen(RESET) + 4;
	user = ft_calloc(user_size, sizeof(char));
	if (!user)
		return (NULL);
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
	t_env	*home_path;
	char	*dir;

	if (!dir_nd)
		return (NULL);
	if (ft_strlen(dir_nd->content) > 1)
		dir_name = ft_strrchr(dir_nd->content, '/') + 1;
	else
		dir_name = dir_nd->content;
	dir_size = ft_strlen(dir_name);
	dir_size += ft_strlen(BGRN) + ft_strlen(RESET) + 4;
	dir = ft_calloc(dir_size, sizeof(char));
	if (!dir)
		return (NULL);
	ft_strcat(dir, BGRN);
	home_path = exist_env_elem(env, "HOME");
	if (home_path && !ft_strcmp(home_path->content, dir_nd->content))
		ft_strcat(dir, "~");
	else
		ft_strcat(dir, dir_name);
	ft_strcat(dir, RESET);
	ft_strcat(dir, " > ");
	return (dir);
}

static char	*create_prompt(t_env *env)
{
	char	*prompt;
	char	*user;
	char	*dir;

	if (!env)
		return (NULL);
	user = get_user(exist_env_elem(env, "USER"));
	dir = get_dir(exist_env_elem(env, "PWD"), env);
	if (!user || !dir)
	{
		clean_strs(user, dir);
		return (NULL);
	}
	prompt = ft_calloc(ft_strlen(user) + ft_strlen(dir) + 1, sizeof(char));
	if (!prompt)
	{
		clean_strs(user, dir);
		return (NULL);
	}
	ft_strcat(prompt, user);
	ft_strcat(prompt, dir);
	clean_strs(user, dir);
	return (prompt);
}

static void	clean_strs(char *s1, char *s2)
{
	free_str(s1);
	free_str(s2);
}
