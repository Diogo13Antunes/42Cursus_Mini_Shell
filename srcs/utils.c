/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:39:55 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_node_redir(t_node *node)
{
	if (!node)
		return (0);
	if (node->id >= ID_IN_REDIR && node->id <= ID_OUT_APPEND)
		return (1);
	return (0);
}

int	is_node_pipe(t_node *node)
{
	if (!node)
		return (0);
	if (node->id == ID_PIPE)
		return (1);
	return (0);
}

int	is_node_cmd(t_node *node)
{
	if (!node)
		return (0);
	if (node->id == ID_CMD)
		return (1);
	return (0);
}

int	is_node_hdoc(t_node *node)
{
	if (!node)
		return (0);
	if (node->id == ID_IN_HERDOC)
		return (1);
	return (0);
}

int	get_matrix_size(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
			i++;
	}
	return (i);
}
