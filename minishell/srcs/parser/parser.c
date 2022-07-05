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

static void		create_ast(t_node **tree, char *token, t_env *env);
static t_node	*get_node_to_update(t_node *tree);

t_node	*parser(char *src, t_env *env)
{
	char	*token;
	t_node	*tree;

	tree = NULL;
	token = get_next_token(src, 1);
	while (token)
	{
		if (get_token_id(token) == ID_WORD)
			token = token_parser(token, env);
		create_ast(&tree, token, env);
		free(token);
		token = get_next_token(src, 0);
		if (is_syntax_error(tree, token))
		{
			//Fazer free da tree
			return (NULL);
		}
	}
	return (tree);
}

static void	create_ast(t_node **tree, char *token, t_env *env)
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
