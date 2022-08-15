/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:12 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		create_ast(t_node **tree, char *token, t_env *env);
static t_node	*get_node_to_update(t_node *tree);

t_node	*parser(char *src, t_env *env, int *exit_code)
{
	char	*token;
	t_node	*tree;
	int		i;

	tree = NULL;
	i = 1;
	while (1)
	{
		token = get_next_token(src, i);
		if (is_syntax_error(tree, token))
		{
			// fazer free da tree
			*exit_code = EXIT_SYNTAX;
			return (NULL);
		}
		if (!token)
			break ;
		if (get_token_id(token) == ID_WORD)
			token = token_parser(token, env, *exit_code);
		create_ast(&tree, token, env);
		free(token);
		i = 0;
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
