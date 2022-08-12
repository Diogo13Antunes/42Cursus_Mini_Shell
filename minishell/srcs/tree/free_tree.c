/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:59:13 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:04 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_node(t_node *node);

void	free_tree(t_node *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->rigth);
	free_node(tree);
}

static void	free_node(t_node *node)
{
	if (is_node_hdoc(node))
		free(((t_hdoc *) node->data)->end);
	else if (is_node_redir(node))
		free(((t_redir *) node->data)->redir);
	else if (is_node_cmd(node))
		free_matrix(((t_cmd *) node->data)->cmd);
	free(node->data);
	free(node);
}
