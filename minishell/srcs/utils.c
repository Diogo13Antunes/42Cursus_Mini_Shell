/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:39:55 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:04 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	get_size_string_array(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
