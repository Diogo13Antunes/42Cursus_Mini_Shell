/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:05:02 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/22 09:10:01 by dsilveri         ###   ########.fr       */
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

int convert_hdoc_stop_code(int code)
{
	if (code == HDOC_STOP_CTRL_C)
		return (EXIT_CTRLC_SIGNAL);
	else
		return (EXIT_SUCCESS);
}
