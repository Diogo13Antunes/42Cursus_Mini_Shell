/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:13:59 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/08 16:13:59 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_path(char *cmd, char **paths);
static void	check_path(char *path, char *cmd);
static char	**get_paths_matrix(t_env *path);
static int	is_cmd_path(char *cmd);

/*Tem de se fazer free dos paths */
char	*get_cmd_path(char *cmd, t_env *env)
{
	char	*path;
	char	**paths;

	paths = get_paths_matrix(exist_env_elem(env, "PATH"));
	if (is_cmd_path(cmd))
		path = ft_strdup(cmd);
	else
		path = find_cmd_path(cmd, paths);
	check_path(path, cmd);
	return (path);
}

static char	*find_cmd_path(char *cmd, char **paths)
{
	char	*path;
	int		size;
	int		i;

	if (!ft_strlen(cmd))
		return (NULL);
	i = 0;
	while (paths[i])
	{
		size = ft_strlen(paths[i]) + ft_strlen(cmd) + 1;
		path = ft_calloc(size + 1, sizeof(char));
		ft_strcat(path, paths[i]);
		ft_strcat(path, "/");
		ft_strcat(path, cmd);
		if (!access(path, F_OK))
			return (path);
		else
			free(path);
		i++;
	}
	return (NULL);
}

static void	check_path(char *path, char *cmd)
{
	struct stat	path_stat;
	int			err;

	cmd_not_found_error(path, cmd);
	err = access(path, X_OK);
	if (err)
	{
		free(path);
		cmd_path_error(err, strerror(errno), cmd);
	}
	err = stat(path, &path_stat);
	if (err)
	{
		free(path);
		cmd_path_error(err, strerror(errno), cmd);
	}
	if (!S_ISREG(path_stat.st_mode))
	{
		free(path);
		cmd_path_error(-1, "Is a directory", cmd);
	}
}

static char	**get_paths_matrix(t_env *path)
{
	char	**paths;

	if (!path)
		return (NULL);
	paths = ft_split(path->content, ':');
	return (paths);
}

static int	is_cmd_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
