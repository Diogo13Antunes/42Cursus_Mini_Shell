/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:37:42 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:04 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	builtin_cd(char **args, t_env *env)
{
	char	*pwd;
	char	*oldpwd;
	t_env	*temp;

	temp = env;
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (-1);
	if (chdir(args[1]))
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		perror(args[1]);
		free_str(oldpwd);
		return (-1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (-1);
	set_env_pwd(temp, pwd, "PWD");
	set_env_pwd(temp, oldpwd, "OLDPWD");
	free_str(pwd);
	free_str(oldpwd);
	return (0);
}
