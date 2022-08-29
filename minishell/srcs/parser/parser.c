/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:12 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/29 17:20:32 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		sytax_error(t_node *tree, char *token);
static void		create_ast(t_node **tree, char *token, t_env *env, int t_id);
static t_node	*get_node_to_update(t_node *tree);

t_node	*parser(char *src, t_env *env, int *exit_code)
{
	char	*token;
	t_node	*tree;
	int		reset;
	int		token_id;

	tree = NULL;
	reset = 1;
	while (1)
	{
		token = get_next_token(src, reset);
		*exit_code = sytax_error(tree, token);
		if (*exit_code)
			return (NULL);
		if (!token)
			break ;
		token_id = get_token_id(token);
		if (token_id == ID_WORD)
			token = token_parser(token, env, *exit_code);
		create_ast(&tree, token, env, token_id);
		free_str(token);
		reset = 0;
	}
	return (tree);
}

static int	sytax_error(t_node *tree, char *token)
{
	if (is_syntax_error(tree, token))
	{
		free_tree(tree);
		free_str(token);
		return (EXIT_SYNTAX);
	}
	return (0);
}

static void	create_ast(t_node **tree, char *token, t_env *env, int t_id)
{
	int		id;
	t_node	*node;

	if (t_id == ID_WORD)
	{
		node = get_node_to_update(*tree);
		if (node)
			update_node(node, token);
		else
			add_new_node(tree, update_node(create_node(ID_CMD), token));
	}
	else
		add_new_node(tree, create_node(t_id));
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
