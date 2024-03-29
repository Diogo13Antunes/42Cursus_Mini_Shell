/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:06 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(int id)
{
	t_node	*node;

	node = oom_guard(malloc(sizeof(t_node)));
	if (!node)
		return (0);
	node->id = id;
	node->data = NULL;
	node->prev = NULL;
	node->left = NULL;
	node->rigth = NULL;
	return (node);
}

void	add_node_after_on_left(t_node *node, t_node *new_node)
{
	if (!node || !new_node)
		return ;
	if ((node->left))
	{
		new_node->left = node->left;
		node->left->prev = new_node;
	}
	node->left = new_node;
	new_node->prev = node;
}

void	add_node_after_on_right(t_node *node, t_node *new_node)
{
	if (!node || !new_node)
		return ;
	if ((node->rigth))
	{
		new_node->left = node->rigth;
		node->rigth->prev = new_node;
	}
	node->rigth = new_node;
	new_node->prev = node;
}

void	add_node_on_top(t_node **tree, t_node *node)
{
	t_node	*first;

	first = *tree;
	if (!first)
		first = node;
	else
	{
		node->left = first;
		first->prev = node;
		first = node;
	}
	*tree = first;
}
