/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:37:42 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/30 16:59:26 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_elemet_content(t_env *env, char *elemt_name);
static int	set_directory(t_env *env, char *path);
static void	set_env_pwd(t_env *env, char *pwd, char *option);

int	builtin_cd(char **args, t_env *env)
{
	char	*path;

	if (get_matrix_size(args) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_BUILTIN);
	}
	if (get_matrix_size(args) == 1 || !ft_strcmp(args[1], "~"))
		path = get_elemet_content(env, "HOME");
	else
		path = args[1];
	if (!path)
	{
		print_msg_error("HOME not set", "cd");
		return (0);
	}
	if (set_directory(env, path))
		return (EXIT_BUILTIN);
	return (0);
}

static char	*get_elemet_content(t_env *env, char *elemt_name)
{
	t_env	*elemt;
	char	*elemt_cont;

	elemt = exist_env_elem(env, elemt_name);
	if (!elemt || !elemt->content)
		return (NULL);
	elemt_cont = elemt->content;
	return (elemt_cont);
}

static int	set_directory(t_env *env, char *path)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (1);
	if (chdir(path))
	{
		free_str(oldpwd);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	set_env_pwd(env, pwd, "PWD");
	set_env_pwd(env, oldpwd, "OLDPWD");
	free_str(pwd);
	free_str(oldpwd);
	return (0);
}

static void	set_env_pwd(t_env *env, char *pwd, char *option)
{
	t_env	*temp;

	temp = env;
	while (temp->next != NULL)
	{
		if (!ft_strncmp(temp->variable, option, ft_strlen(option) + 1))
			break ;
		temp = temp->next;
	}
	free_str(temp->full);
	free_str(temp->content);
	temp->content = ft_substr(pwd, 0, ft_strlen(pwd));
	temp->full = create_full_env(temp->variable, temp->content);
}
