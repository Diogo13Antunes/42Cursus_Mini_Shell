/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:37:56 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/13 11:37:58 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LEFT 	0
#define RIGHT 	1

static void	add_new_redir(t_node **tree, t_node *node);
static void	add_new_cmd(t_node **tree, t_node *node);
static void	add_new_pipe(t_node **tree, t_node *node);

void	add_new_node(t_node **tree, t_node *node)
{
	if (is_node_redir(node))
		add_new_redir(tree, node);
	else if (is_node_cmd(node))
		add_new_cmd(tree, node);
	else if (is_node_pipe(node))
		add_new_pipe(tree, node);
}

static void	add_new_redir(t_node **tree, t_node *node)
{
	t_node	*first;
	t_node	*next;	

	if (!tree)
		return ;
	first = *tree;
	if (!first || is_node_redir(first))
		add_node_on_top(tree, node);
	else if (is_node_cmd(first))
		add_node_after_on_left(first, node);
	else if (is_node_pipe(first))
	{
		next = first->rigth;
		if (!next || is_node_redir(next))
			add_node_after_on_right(first, node);
		else
			add_node_after_on_left(next, node);
	}
}

static void	add_new_cmd(t_node **tree, t_node *node)
{
	t_node	*first;

	first = *tree;
	if (!first || is_node_redir(first))
		add_node_on_top(tree, node);
	else if (is_node_pipe(first))
		add_node_after_on_right(first, node);
}

static void	add_new_pipe(t_node **tree, t_node *node)
{
	add_node_on_top(tree, node);
}
