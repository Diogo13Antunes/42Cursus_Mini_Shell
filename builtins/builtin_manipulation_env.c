/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manipulation_env.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:33:39 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/15 10:23:48 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

t_env	*create_new_env_elem(char *var, char *cont)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->variable = var;
	elem->content = cont;
	elem->full = create_full_env(var, cont);
	elem->next = NULL;
	return (elem);
}

t_env	*get_new_env_elem(char *env_str)
{
	t_env	*elem;
	char	*var;
	char	*cont;
	int		i;

	i = find_char(env_str, '=');
	if (i > 0)
	{
		var = ft_substr(env_str, 0, i);
		cont = ft_substr(env_str, i + 1, ft_strlen(env_str));
	}
	else
	{
		var = ft_substr(env_str, 0, ft_strlen(env_str));
		cont = NULL;
	}
	elem = create_new_env_elem(var, cont);
	return (elem);
}

void	ft_update_elem(t_env *elem, char *element)
{
	int		i;

	i = find_char(element, '=');
	if (i < 0)
		return ;
	if (elem->content)
		free(elem->content);
	if (elem->full)
		free(elem->full);
	elem->content = ft_substr(element, i + 1, ft_strlen(element));
	elem->full = create_full_env(elem->variable, elem->content);
}
