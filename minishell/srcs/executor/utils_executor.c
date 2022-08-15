/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:05:02 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > -1)
		close(fd);
}

int	get_num_cmds(t_node *tree)
{
	t_node	*node;
	int		i;

	node = tree;
	if (!is_node_pipe(node))
		return (1);
	i = 1;
	while (is_node_pipe(node))
	{
		node = node->left;
		i++;
	}
	return (i);
}
