/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:43:04 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/24 12:31:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	open_pipe(void)
{
	t_pipe	p;
	int		fd_p[2];

	sys_error(pipe(fd_p), "pipe");
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
		sys_error(pipe(fd_p), "pipe");
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
				sys_error(dup2(p->w, STDOUT_FILENO), "dup2");
			else if (node->rigth == buff)
			{
				sys_error(dup2(p->r, STDIN_FILENO), "dup2");
				if (node->prev)
				{
					p = (t_pipe *)(node->prev->data);
					sys_error(dup2(p->w, STDOUT_FILENO), "dup2");
				}
			}
			close_pipes(node);
		}
		buff = node;
		node = node->prev;
	}
}
