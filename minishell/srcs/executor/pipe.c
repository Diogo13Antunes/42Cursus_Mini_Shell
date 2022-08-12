/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:43:04 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:04 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		p = oom_guard(malloc(sizeof(t_pipe)));
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

void	pipe_redir(t_node *node)
{
	t_node	*buff;
	t_pipe	*p;

	buff = node;
	while (node)
	{
		if (is_node_pipe(node))
		{
			p = (t_pipe *)(node->data);
			if (node->left == buff)
				dup2(p->w, STDOUT_FILENO);
			else if (node->rigth == buff)
			{
				dup2(p->r, STDIN_FILENO);
				if (node->prev)
				{
					p = (t_pipe *)(node->prev->data);
					dup2(p->w, STDOUT_FILENO);
				}
			}
			close_pipes(node);
		}
		buff = node;
		node = node->prev;
	}
}
