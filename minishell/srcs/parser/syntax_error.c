/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:43 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/05 12:10:45 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	branch_analysis(t_node *node, char *token);
static void	print_error(char *token);

int	is_syntax_error(t_node *tree, char *token)
{
	int	status;

	if (!tree)
		return (0);
	status = 0;
	if (!token || get_token_id(token) != ID_WORD)
	{
		if (!is_node_pipe(tree))
			status = branch_analysis(tree, token);
		else
			status = branch_analysis(tree->rigth, token);
	}
	return (status);
}

static int	branch_analysis(t_node *node, char *token)
{
	if (!token && !node)
		print_error(token);
	if (!node && get_token_id(token) == ID_PIPE)
		print_error(token);
	while (node)
	{
		if (!(node->data))
		{
			print_error(token);
			return (1);
		}
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
