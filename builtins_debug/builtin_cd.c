/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:59:59 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/01 11:32:09 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	print_pwd(t_env *env, char *option)
{
	t_env	*temp;

	temp = env;
	while (temp->next != NULL)
	{
		if (!ft_strncmp(temp->variable, option, ft_strlen(option) + 1))
			break ;
		temp = temp->next;
	}
	ft_putstr_fd(temp->full, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

//! Rever depois onde ficar 
void	free_str(char *str)
{
	if (str)
		free(str);
}

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

int	builtin_cd(char *path, t_env *env)
{
	char	*pwd;
	char	*oldpwd;
	t_env	*temp;

	temp = env;
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (-1);
	if (chdir(path))
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		perror(path);
		free(oldpwd);
		return (-1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (-1);
	set_env_pwd(temp, pwd, "PWD");
	set_env_pwd(temp, oldpwd, "OLDPWD");
	free(pwd);
	free(oldpwd);
	return (0);
}

int	main(int ac, char **av, char **enviroment)
{
	t_env	*env;

	if (ac != 2)
	{
		ft_putstr_fd("Error: Invalid number of arguments", STDERR_FILENO);
		return (-1);
	}
	env = get_env_list(enviroment);
	if (builtin_cd(av[1], env) != 0)
		return (-1);
	print_pwd(env, "PWD");
	print_pwd(env, "OLDPWD");
	return (0);
}
