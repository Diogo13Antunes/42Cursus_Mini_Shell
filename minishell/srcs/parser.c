/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:12 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/14 12:10:43 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_ast(t_node **tree, char *token);
int			get_node_id(char *token);
int			get_token_id(char *token);
t_node		*get_node_to_update(t_node *tree);
t_node		*update_node(t_node *node, char *token);

void	print_node(t_node *node)
{
	if (!node)
	{
		printf("Node not exist's\n");
		return ;
	}
	printf("##########################\n");
	printf("node add: %p\n", node);
	printf("node id: %i\n", node->id);
	//printf("node data: %s\n", node->data);
	printf("node prev: %p\n", node->prev);
	printf("node left: %p\n", node->left);
	printf("node rigth: %p\n", node->rigth);
	printf("##########################\n");
}

t_node	*parser(char *src)
{
	char	*token;
	t_node	*tree;
	t_node	*tree_b;

	tree = NULL;
	token = get_next_token(src);
	while (token)
	{
		create_ast(&tree, token);
		token = get_next_token(src);
	}
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
			update_node(node, token);
		else
			add_new_node(tree, update_node(create_node(ID_CMD), token));
	}
	else
		add_new_node(tree, create_node(id));
}

t_node	*get_node_to_update(t_node *tree)
{
	t_node	*node;
	t_node	*next;

	if (!tree)
		return (NULL);
	if (is_node_pipe(*tree))
		node = tree->rigth;
	else
		node = tree;
	if (!node)
		return (NULL);
	next = node->left;
	if ((is_node_redir(*node) && !(node->data)))
		return (node);
	else if (next && is_node_redir(*next) && !(next->data))
		return (next);
	else if (is_node_cmd(*node))
		return (node);
	return (NULL);
}

int	get_size_string_array(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**update_string_array(char **str, char *token)
{
	char	**new_arr;
	char	**buff;
	int		arr_size;
	int		i;

	if (!str)
	{
		new_arr = malloc(2 * sizeof(char *));
		new_arr[0] = ft_strdup(token);
		new_arr[1] = NULL;
	}
	else
	{
		arr_size = get_size_string_array(str);
		new_arr = malloc((arr_size + 2) * sizeof(char *));
		i = -1;
		while (str[++i])
			new_arr[i] = str[i];
		new_arr[i] = ft_strdup(token);
		new_arr[i + 1] = 0;
		free(str);
	}
	return (new_arr);
}

t_node	*update_node(t_node *node, char *token)
{
	int	size;

	if (!node || !token)
		return (NULL);
	node->data = update_string_array(node->data, token);
	return (node);
}

int	get_token_id(char *token)
{
	int	size;

	size = ft_strlen(token);
	if (size == 1)
	{
		if (token[0] == '<')
			return (ID_IN_REDIR);
		else if (token[0] == '>')
			return (ID_OUT_REDIR);
		else if (token[0] == '|')
			return (ID_PIPE);
	}
	if (size == 2)
	{
		if (token[0] == '<' && token[1] == '<')
			return (ID_IN_HERDOC);
		else if (token[0] == '>' && token[1] == '>')
			return (ID_OUT_HERDOC);
	}
	return (ID_WORD);
}

int	is_node_redir(t_node node)
{
	if (node.id >= ID_IN_REDIR && node.id <= ID_OUT_HERDOC)
		return (1);
	return (0);
}

int	is_node_pipe(t_node node)
{
	if (node.id == ID_PIPE)
		return (1);
	return (0);
}

int	is_node_cmd(t_node node)
{
	if (node.id == ID_CMD)
		return (1);
	return (0);
}
