/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:39:56 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/15 11:16:26 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	env_lst_size(t_env *env)
{
	t_env	*elem;
	int		counter;

	elem = env;
	counter = 0;
	while (elem)
	{
		if (elem->content)
			counter++;
		elem = elem->next;
	}
	return (counter);
}

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !c)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
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
		if (!ft_strncmp(temp->variable, elem_name, size))
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

char	*create_full_env(char *var, char *cont)
{
	char	*final_str;
	int		len;

	len = ft_strlen(var) + ft_strlen(cont) + 2;
	final_str = ft_calloc(sizeof(char), len);
	ft_strlcat(final_str, var, len);
	ft_strlcat(final_str, "=", len);
	ft_strlcat(final_str, cont, len);
	return (final_str);
}

t_env	*get_env_list(char **env)
{
	int		i;
	t_env	*list;

	i = 0;
	list = NULL;
	while (env[i])
	{
		ft_lstadd_back(&list, get_new_env_elem(env[i]));
		i++;
	}
	if (!exist_env_elem(list, "OLDPWD"))
		ft_lstadd_back(&list, create_new_env_elem("OLDPWD", 0));
	return (list);
}
