/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:39:55 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/21 12:42:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_node_redir(t_node *node)
{
	if (!node)
		return (0);
	if (node->id >= ID_IN_REDIR && node->id <= ID_OUT_HERDOC)
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
