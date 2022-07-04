/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:43:04 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/27 09:43:04 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	open_pipe(void)
{
	t_pipe	p;
	int		fd_p[2];

	pipe(fd_p);
	p.r = fd_p[0];
	p.w = fd_p[1];
	return (p);
}

void	close_pipe(t_pipe pipe)
{
	close(pipe.r);
	close(pipe.w);
}

void	open_pipes(t_node *tree)
{
	t_pipe	*p;
	int		fd_p[2];

	if (tree == NULL)
		return ;
	open_pipes(tree->left);
	if (is_node_pipe(tree))
	{
		pipe(fd_p);
		p = malloc(sizeof(t_pipe));
		if (!p)
			return ;
		p->r = fd_p[0];
		p->w = fd_p[1];
		tree->data = (void *) p;
	}
}

void	close_pipes(t_node *tree)
{
	t_node	*node;

	node = tree;
	while (node)
	{
		if (is_node_pipe(node))
			close_pipe(*((t_pipe *)(node->data)));
		node = node->left;
	}
	node = tree;
	while (node)
	{
		if (is_node_pipe(node))
			close_pipe(*((t_pipe *)(node->data)));
		node = node->prev;
	}
}
