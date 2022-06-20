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

//cat <in teste  >out | ls <in2 >out2 -la | <<in3 >>out3 grep "jun"

#include "minishell.h"

#define LEFT 	0
#define RIGHT 	1

void	add_new_redir(t_node **tree, t_node *node);
void	add_new_cmd(t_node **tree, t_node *node);
void	add_new_pipe(t_node **tree, t_node *node);
void	add_node_after_left(t_node *node, t_node *new_node);

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

void	add_node_after(t_node *node, t_node *new_node, int dir)
{
	if (!node || !new_node)
		return ;
	else if (dir == LEFT && (node->left))
	{
		new_node->left = node->left;
		node->left->prev = new_node;
	}
	else if (dir == RIGHT && (node->rigth))
	{
		new_node->left = node->rigth;
		node->rigth->prev = new_node;
	}
	if (dir == LEFT)
		node->left = new_node;
	else if (dir == RIGHT)
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

void	add_new_node(t_node **tree, t_node *node)
{
	if (is_node_redir(node))
		add_new_redir(tree, node);
	else if (is_node_cmd(node))
		add_new_cmd(tree, node);
	else if (is_node_pipe(node))
		add_node_on_top(tree, node);
}

void	add_new_redir(t_node **tree, t_node *node)
{
	t_node	*first;
	t_node	*next;	

	if (!tree)
		return ;
	first = *tree;
	if (!first || is_node_redir(first))
		add_node_on_top(tree, node);
	else if (is_node_cmd(first))
		add_node_after(first, node, LEFT);
	else if (is_node_pipe(first))
	{
		next = first->rigth;
		if (!next || is_node_redir(next))
			add_node_after(first, node, RIGHT);
		else
			add_node_after(next, node, LEFT);
	}
}

void	add_new_cmd(t_node **tree, t_node *node)
{
	t_node	*first;

	first = *tree;
	if (!first || is_node_redir(first))
		add_node_on_top(tree, node);
	else if (is_node_pipe(first))
		add_node_after(first, node, RIGHT);
}
