/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:12 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/09 18:02:26 by dsilveri         ###   ########.fr       */
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
	printf("node add: %p\n", node);
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
	/*int i = 0;
	if (tree)
	{
		tree_b = tree;
		while (tree_b)
		{
			print_node(tree_b);
			//if (i == 0)
			//	tree_b = tree_b->rigth;
			//else 
				tree_b = tree_b->left;
			i++;
		}
	}*/

	print2D(tree);

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

/*
	Esta função dever ser melhorada e faze-la de forma mais simple
*/
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
	else //navega pela direita
	{
		node = tree;
		if (node->rigth == NULL)
			return (NULL);
		else if (node->rigth && is_node_redir(*(node->rigth)) && node->rigth->data == NULL)
			return(node->rigth);
		else if (node->rigth->left && is_node_redir(*(node->rigth->left)) && node->rigth->left->data == NULL)
			return(node->rigth->left);

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