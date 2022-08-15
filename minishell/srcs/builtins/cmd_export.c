/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:10:13 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	builtin_export(t_env *env, char **elems, int fd)
{
	int		i;
	t_env	*exist;

	if (!elems[1])
	{
		print_export(env, fd);
		return ;
	}
	i = 1;
	while (elems[i])
	{
		if (check_element(elems[i]))
		{
			exist = exist_env_elem(env, elems[i]);
			if (exist)
				ft_update_elem(exist, elems[i]);
			else
				ft_lstadd_back_env(&env, get_new_env_elem(elems[i]));
		}
		i++;
	}
	return ;
}
