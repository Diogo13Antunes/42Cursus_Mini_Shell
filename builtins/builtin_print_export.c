/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:05:15 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/15 11:07:44 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	print_element(t_env	elem, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(elem.variable, fd);
	if (elem.content)
	{
		ft_putstr_fd("=", fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(elem.content, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd("\n", fd);
}

void	get_variables(t_env *env, char **vars)
{
	t_env	*temp;
	int		size_list;
	int		i;

	i = 0;
	temp = env;
	size_list = ft_lstsize(temp);
	while (temp)
	{
		vars[i] = temp->variable;
		i++;
		temp = temp->next;
	}
}

char	**sorter_env_vars(t_env	*env)
{
	char		**vars;
	int			size_list;
	char		*temp;
	int			i;
	int			j;

	i = -1;
	size_list = ft_lstsize(env);
	vars = ft_calloc(sizeof(char *), size_list + 1);
	get_variables(env, vars);
	while (++i < size_list)
	{
		j = -1;
		while (++j < size_list - 1 - i)
		{
			if (ft_strcmp(vars[j], vars[j + 1]) > 0)
			{
				temp = vars[j];
				vars[j] = vars[j + 1];
				vars[j + 1] = temp;
			}
		}
	}
	return (vars);
}

void	print_export(t_env *env, int fd)
{
	int		i;
	t_env	*temp;
	char	**sort_vars;

	i = 0;
	sort_vars = sorter_env_vars(env);
	while (sort_vars[i])
	{
		temp = env;
		while (temp)
		{
			if (!ft_strcmp(sort_vars[i], temp->variable))
			{
				print_element(*temp, fd);
				i++;
				break ;
			}
			temp = temp->next;
		}
	}
	free(sort_vars);
}
