/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:05:15 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/30 16:13:38 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sorter_env_vars(t_env	*env);
static void	get_variables(t_env *env, char **vars);
static void	print_element(t_env	elem, int fd);

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
	free_matrix(sort_vars);
}

static char	**sorter_env_vars(t_env	*env)
{
	char		**vars;
	char		*temp;
	int			size_list;
	int			i;
	int			j;

	i = -1;
	size_list = env_lst_size(env);
	vars = oom_guard(ft_calloc(sizeof(char *), size_list + 1));
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

static void	get_variables(t_env *env, char **vars)
{
	t_env	*temp;
	int		size_list;
	int		i;

	i = 0;
	temp = env;
	size_list = env_lst_size(temp);
	while (temp)
	{
		vars[i] = temp->variable;
		i++;
		temp = temp->next;
	}
}

static void	print_element(t_env	elem, int fd)
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
