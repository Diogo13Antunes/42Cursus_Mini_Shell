/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:37:42 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_pwd(t_env *env, char *pwd, char *option)
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

char	*get_elemet_content(t_env *env, char *elemt_name)
{
	t_env	*elemt;
	char	*elemt_cont;

	elemt = exist_env_elem(env, elemt_name);
	elemt_cont = elemt->content;
	return (elemt_cont);
}

int	set_directory(t_env *env, char *path)
{
	char 	*pwd;
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
	if (set_directory(env, path))
		return (EXIT_BUILTIN);
	return (0);
}
