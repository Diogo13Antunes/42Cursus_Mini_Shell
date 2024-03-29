/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:10:13 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/30 17:11:10 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TYPE_NAME 1
#define TYPE_CONTENT 2

static int	update_elem(t_env *elem, char *cont);
static char	*get_elem_str_data(char *data, int type);
static void	make_elemt_chages(char *data, t_env *env);

int	builtin_export(t_env *env, char **elems, int fd)
{
	int		i;
	int		return_value;

	if (get_matrix_size(elems) == 1)
	{
		print_export(env, fd);
		return (0);
	}
	i = 1;
	return_value = 0;
	while (elems[i])
	{
		if (ft_strlen(elems[i]))
		{	
			if (check_element(elems[i]))
				make_elemt_chages(elems[i], env);
			else
			{
				print_msg_error2(elems[i], "not a valid identifier", "export");
				return_value = EXIT_BUILTIN;
			}
		}
		i++;
	}
	return (return_value);
}

static void	make_elemt_chages(char *data, t_env *env)
{
	t_env	*element;
	char	*name;

	name = get_elem_str_data(data, TYPE_NAME);
	element = exist_env_elem(env, name);
	free_str(name);
	if (element)
		update_elem(element, get_elem_str_data(data, TYPE_CONTENT));
	else
		ft_lstadd_back_env(&env, get_new_env_elem(data));
}

static int	update_elem(t_env *elem, char *cont)
{
	if (!elem || !cont)
	{
		free_str(cont);
		return (0);
	}
	free_str(elem->content);
	free_str(elem->full);
	elem->content = cont;
	elem->full = create_full_env(elem->variable, elem->content);
	return (1);
}

static char	*get_elem_str_data(char *data, int type)
{
	char	*name;
	char	*cont;
	int		i;

	if (!data)
		return (NULL);
	i = get_char_index(data, '=');
	if (i == -1)
	{
		name = ft_substr(data, 0, ft_strlen(data));
		cont = NULL;
	}
	else
	{
		name = ft_substr(data, 0, i);
		cont = ft_substr(data, i + 1, ft_strlen(data));
	}
	if (type == TYPE_NAME)
	{
		free_str(cont);
		return (name);
	}
	free_str(name);
	return (cont);
}
