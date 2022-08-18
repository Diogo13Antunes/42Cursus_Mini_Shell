/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:38:57 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/15 10:21:40 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	builtin_export(t_env *env, char **elems, int fd)
{
	int		i;
	t_env	*exist;

	if (!elems)
	{
		print_export(env, fd);
		return ;
	}
	i = 0;
	while (elems[i])
	{
		if (check_element(elems[i]))
		{
			exist = exist_env_elem(env, elems[i]);
			if (exist)
				ft_update_elem(exist, elems[i]);
			else
				ft_lstadd_back(&env, get_new_env_elem(elems[i]));
		}
		i++;
	}
	return ;
}
