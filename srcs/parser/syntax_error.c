/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:43 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/29 17:13:01 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_analysis(t_node *tree, char *token);
static int	branch_analysis(t_node *node);
static void	print_error(char *token);

int	is_syntax_error(t_node *tree, char *token)
{
	int	status;

	status = 0;
	if (!token || get_token_id(token) != ID_WORD)
		status = error_analysis(tree, token);
	return (status);
}

static int	error_analysis(t_node *tree, char *token)
{
	t_node	*node;

	if (!tree && token && get_token_id(token) == ID_PIPE)
	{
		print_error(token);
		return (1);
	}
	if (tree)
	{
		if (!token && is_node_pipe(tree) && !tree->rigth)
		{
			print_error(token);
			return (1);
		}		
		if (is_node_pipe(tree))
			node = tree->rigth;
		else
			node = tree;
		if (branch_analysis(node))
		{
			print_error(token);
			return (1);
		}
	}
	return (0);
}

static int	branch_analysis(t_node *node)
{
	while (node)
	{
		if (!(node->data))
			return (1);
		node = node->left;
	}
	return (0);
}

static void	print_error(char *token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
