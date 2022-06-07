/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:12 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/07 19:19:13 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_ast(t_node **tree, char *token);
int get_node_id(char *token);

void print_node(t_node *node)
{
	if (!node)
	{
		printf("Node not exist's\n");
		return ;
	}
	printf("##########################\n");
	printf("node id: %i\n", node->id);
	printf("node prev: %p\n", node->prev);
	printf("node left: %p\n", node->left);
	printf("node rigth: %p\n", node->rigth);
	printf("##########################\n");
}


t_node	*parser(char *src)
{
	char	*token;
	t_node	*tree;
	t_node *tree_b;

	tree = NULL;
	token = get_next_token(src);
	while (token)
	{
		create_ast(&tree, token);
		token = get_next_token(src);
	}
	// Apenas para testes print do brunch da tree
	if (tree)
	{
		tree_b = tree;
		while (tree_b)
		{
			print_node(tree_b);
			tree_b = tree_b->left;
		}
	}
	return (0);
}

static void	create_ast(t_node **tree, char *token)
{
	int		node_id;
	t_node	*node;
	
	node_id = get_node_id(token);
	if (node_id)
		add_new_node(tree, create_node(node_id));
}

/*
static void	create_ast1(t_node **tree, char *token)
{
	int		node_id;
	t_node	*node;
	
	node_id = get_node_id(token);
	if (node_id == ID_WORD)
	{
		node = get_node_to_update(tree);
		if (node)
			update_node(node, token);
		else 
			add_new_node(tree, create_node(ID_CMD));
	}
	else 
		add_new_node(tree, create_node(node_id));
}
*/

int get_node_id(char *token)
{
	int size;

	size = ft_strlen(token);
	if(size == 1)
	{
		if (token[0] == '<')
			return (ID_IN_REDIR);
		else if (token[0] == '>')
			return (ID_OUT_REDIR);
		else if (token[0] == '|')
			return (ID_PIPE);
	}
	if(size == 2)
	{
		if (token[0] == '<' && token[1] == '<')
			return (ID_IN_HERDOC);
		else if (token[0] == '>' && token[1] == '>')
			return (ID_OUT_HERDOC);
	}
	return (ID_WORD);
}

int is_node_redir(t_node node)
{
	if (node.id >= ID_IN_REDIR && node.id <= ID_OUT_HERDOC)
		return (1);
	return (0);
}

int is_node_pipe(t_node node)
{
	if (node.id >= ID_PIPE)
		return (1);
	return (0);
}

int is_node_cmd(t_node node)
{
	if (node.id >= ID_CMD)
		return (1);
	return (0);
}