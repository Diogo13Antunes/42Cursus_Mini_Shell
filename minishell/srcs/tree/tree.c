/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:06 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/18 21:38:01 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(int id)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
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
