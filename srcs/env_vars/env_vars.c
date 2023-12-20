/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:23:03 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/30 17:04:43 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lst_size(t_env *env)
{
	t_env	*elem;
	int		counter;

	elem = env;
	counter = 0;
	while (elem)
	{
		counter++;
		elem = elem->next;
	}
	return (counter);
}

char	**get_env_matrix(t_env *list)
{
	int		lst_size;
	char	**matrix;
	t_env	*temp;
	int		i;

	i = 0;
	temp = list;
	lst_size = env_lst_size(list);
	matrix = oom_guard(ft_calloc(sizeof(char *), lst_size + 1));
	while (temp)
	{
		matrix[i] = temp->full;
		i++;
		temp = temp->next;
	}
	return (matrix);
}

char	*create_full_env(char *var, char *cont)
{
	char	*final_str;
	int		len;

	if (cont)
		len = ft_strlen(var) + ft_strlen(cont) + 2;
	else
		len = ft_strlen(var) + 1;
	final_str = oom_guard(ft_calloc(sizeof(char), len));
	ft_strlcat(final_str, var, len);
	if (cont)
	{
		ft_strlcat(final_str, "=", len);
		ft_strlcat(final_str, cont, len);
	}
	return (final_str);
}

t_env	*exist_env_elem(t_env *env, const char *elem_name)
{
	t_env	*temp;
	int		size;
	char	*ptr;

	temp = env;
	size = ft_strlen(elem_name);
	if (!elem_name)
		return (0);
	ptr = ft_strchr(elem_name, '=');
	if (ptr)
		*ptr = '\0';
	while (temp)
	{
		if (!ft_strncmp(temp->variable, elem_name, size) \
		&& size == (int)ft_strlen(temp->variable))
		{
			if (ptr)
				*ptr = '=';
			return (temp);
		}
		temp = temp->next;
	}
	if (ptr)
		*ptr = '=';
	return (NULL);
}
