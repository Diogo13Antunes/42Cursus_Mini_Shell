/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:12 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/08 11:55:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_ast(t_node **tree, char *token);
int get_node_id(char *token);
int get_token_id(char *token);
t_node *get_node_to_update(t_node *tree);
t_node *update_node(t_node *node, char *token);

void print_node(t_node *node)
{
	if (!node)
	{
		printf("Node not exist's\n");
		return ;
	}
	printf("##########################\n");
	printf("node id: %i\n", node->id);
	printf("node data: %s\n", node->data);
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
	int		id;
	t_node	*node;
	
	id = get_token_id(token);
	if (id == ID_WORD)
	{
		node = get_node_to_update(*tree);
		if (node)
			update_node(node, token); //vai fazer update de comandos também regra ainda não criada
		else
			add_new_node(tree, update_node(create_node(ID_CMD), token));
	}
	else 
		add_new_node(tree, create_node(id));
}

t_node *get_node_to_update(t_node *tree)
{
	t_node *node;

	if (!tree)
		return (NULL);
	if (tree->id != ID_PIPE) // Navega pela esquerda
	{
		node = tree;
		while (node)
		{
			if (is_node_redir(*node))
			{
				if (!(node->data))
					return (node);
				else
					break;
			}
			node = node->left;
		}
	}
	return (NULL);
}

// apenas resolve strings no futuro terá de ser array de string
t_node *update_node(t_node *node, char *token)
{
	int size;

	if (!node)
		return (NULL);
	if (!(node->data))
	{
		size = ft_strlen(token);
		node->data = ft_calloc(size + 1, sizeof(char));
		if (!(node->data))
			return (NULL);
		ft_strlcpy(node->data, token, size + 1);
	}
	return (node);
}


int get_token_id(char *token)
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