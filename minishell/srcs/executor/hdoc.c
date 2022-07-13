/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:41:07 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/04 18:41:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hdoc_exec2(t_node *node);

void	hdoc_exec(t_node *tree)
{
	if (tree == NULL)
		return ;
	hdoc_exec(tree->left);
	if (is_node_hdoc(tree))
		hdoc_exec2(tree);
	hdoc_exec(tree->rigth);
}

static void	hdoc_exec2(t_node *node)
{
	t_pipe	p;
	t_hdoc	*h;
	char	*str;

	h = (t_hdoc *)(node->data);
	p = open_pipe();
	h->p = p;
	while (1)
	{
		str = readline("heredoc> ");
		if (!ft_strcmp(h->end, str))
			break ;
		ft_putstr_fd(str, p.w);
		ft_putstr_fd("\n", p.w);
		free(str);
	}
	free(str);
}

void	close_hdoc(t_node *tree)
{
	t_pipe	p;

	if (tree == NULL)
		return ;
	p = ((t_hdoc *)(tree->data))->p;
	close_hdoc(tree->left);
	if (is_node_hdoc(tree))
		close_pipe(p);
	close_hdoc(tree->rigth);
}

void	hdoc_redir(t_node *node)
{
	t_pipe	p;

	p = ((t_hdoc *)(node->data))->p;
	dup2(p.r, STDIN_FILENO);
	close_pipe(p);
}
