/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:25:13 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/06 12:14:04 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

/**==============================================
 * todo                  TODO
 *
 *   update_env_elem(t_env **list, char *elem);
 *   char **get_env_matrix(t_env *list);
 *   free_list(t_env *list);
 *   free_env_m(char **m);
 *   fazer verificacao da variavel de ambiente
 *
 *=============================================**/

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
