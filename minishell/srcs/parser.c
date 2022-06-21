/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:12 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/21 15:41:26 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		create_ast(t_node **tree, char *token);
static t_node	*get_node_to_update(t_node *tree);
static t_node	*update_node(t_node *node, char *token);

t_node	*parser(char *src)
{
	char	*token;
	t_node	*tree;

	tree = NULL;
	token = get_next_token(src);
	while (token)
	{
		create_ast(&tree, token);
		token = get_next_token(src);
	}
	return (tree);
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

static t_node	*get_node_to_update(t_node *tree)
{
	t_node	*node;
	t_node	*next;

	if (!tree)
		return (NULL);
	if (is_node_pipe(tree))
		node = tree->rigth;
	else
		node = tree;
	if (!node)
		return (NULL);
	next = node->left;
	if ((is_node_redir(node) && !(node->data)))
		return (node);
	else if (next && is_node_redir(next) && !(next->data))
		return (next);
	else if (is_node_cmd(node))
		return (node);
	return (NULL);
}

static t_node	*update_node(t_node *node, char *token)
{
	int		size;
	t_redir	*r;
	t_cmd	*c;

	if (!node || !token)
		return (NULL);
	if (is_node_redir(node))
	{
		r = malloc(sizeof(t_redir));
		r->redir = ft_strdup(token);
		node->data = (void *) r;
	}
	else if (is_node_cmd(node))
	{
		if (!(node->data))
		{
			c = malloc(sizeof(t_cmd));
			c->cmd = NULL;
		}
		else
			c = (t_cmd *) node->data;
		c->cmd = update_string_array(c->cmd, token);
		node->data = (void *) c;
	}
	return (node);
}
