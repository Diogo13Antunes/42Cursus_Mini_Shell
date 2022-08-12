/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:58:35 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:04 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_env firt_elem, int fd)
{
	t_env	elem;

	elem = firt_elem;
	while (elem.next != NULL)
	{
		if (elem.content)
		{
			ft_putstr_fd(elem.full, fd);
			ft_putstr_fd("\n", fd);
		}
		elem = *(elem.next);
	}
	if (elem.content)
	{
		ft_putstr_fd(elem.full, fd);
		ft_putstr_fd("\n", fd);
	}
}
