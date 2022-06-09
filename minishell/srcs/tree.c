/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:06 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/09 12:46:54 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_new_redir(t_node **tree, t_node *node);
void add_new_cmd(t_node **tree, t_node *node);
void add_new_pipe(t_node **tree, t_node *node);

void add_node_after_left(t_node *node, t_node *new_node);

t_node  *create_node(int id)
{
	t_node *node;

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

void add_node_after_left(t_node *node, t_node *new_node)
{
	if (!node || !new_node)
		return ;
	new_node->prev = node;
	if ((node->left))
	{
		new_node->left = node->left;
		node->left->prev = new_node;
	}
	node->left = new_node;
}

void add_node_after_right(t_node *node, t_node *new_node)
{
	if (!node || !new_node)
		return ;
	if(node->rigth)
	{
		new_node->left = node->rigth;
		node->rigth->prev = new_node;
	}
	new_node->prev = node;
	node->rigth = new_node;
}

void add_node_on_top(t_node **tree, t_node *node)
{
	t_node *first;

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

void add_new_node(t_node **tree, t_node *node)
{
	if (is_node_redir(*node))
		add_new_redir(tree, node);
	else if (is_node_cmd(*node))
		add_new_cmd(tree, node);
	else if (is_node_pipe(*node))
		add_new_pipe(tree, node);
}

void add_new_redir(t_node **tree, t_node *node)
{
	t_node	*first;
	t_node	*next;	

	if (!tree)
		return ;
	first = *tree;
	if (!first || is_node_redir(*first))
		add_node_on_top(tree, node);
	else if (is_node_cmd(*first))
		add_node_after_left(first, node);
	else if (is_node_pipe(*first))
	{
		next = first->rigth;
		if (!next || is_node_redir(*next))	
			add_node_after_right(first, node);
		else
			add_node_after_left(next, node);
	}
}

void add_new_cmd(t_node **tree, t_node *node)
{
	t_node *first;
	
	first = *tree;
	if (!first || is_node_redir(*first))
		add_node_on_top(tree, node);
	else if (is_node_pipe(*first))
		add_node_after_right(first, node);
}

void add_new_pipe(t_node **tree, t_node *node)
{
	t_node *first;
	
	first = *tree;
	if (!first)
		printf("Não pode e erro de sintax/parser. O pipe não pode ser o primeiro\n");
	else if (first->id != ID_CMD && first->id != ID_PIPE)
		printf("Não pode e erro de sintax/parser. O pipe não pode ser o primeiro\n");
	else
		add_node_on_top(tree, node);
}