/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:49:29 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/30 17:08:36 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_node_cmd(t_node *node, char *token);
static void	update_node_redir(t_node *node, char *token);
static void	update_node_hdoc(t_node *node, char *token);
static char	**update_string_array(char **str, char *token);

t_node	*update_node(t_node *node, char *token)
{
	if (!node || !token)
		return (NULL);
	if (is_node_hdoc(node))
		update_node_hdoc(node, token);
	else if (is_node_redir(node))
		update_node_redir(node, token);
	else if (is_node_cmd(node))
		update_node_cmd(node, token);
	return (node);
}

static void	update_node_cmd(t_node *node, char *token)
{
	t_cmd	*c;

	if (!node && !token)
		return ;
	if (!(node->data))
	{
		c = oom_guard(malloc(sizeof(t_cmd)));
		c->cmd = NULL;
	}
	else
		c = (t_cmd *) node->data;
	c->cmd = update_string_array(c->cmd, token);
	node->data = (void *) c;
}

static void	update_node_redir(t_node *node, char *token)
{
	t_redir	*r;

	if (!node && !token)
		return ;
	r = oom_guard(malloc(sizeof(t_redir)));
	r->redir = oom_guard(ft_strdup(token));
	node->data = (void *) r;
}

static void	update_node_hdoc(t_node *node, char *token)
{
	t_hdoc	*h;

	if (!node && !token)
		return ;
	h = oom_guard(malloc(sizeof(t_hdoc)));
	h->end = oom_guard(ft_strdup(token));
	h->p.r = -1;
	h->p.w = -1;
	node->data = (void *) h;
}

static char	**update_string_array(char **str, char *token)
{
	char	**new_arr;
	int		arr_size;
	int		i;

	if (!str)
	{
		new_arr = oom_guard(malloc(2 * sizeof(char *)));
		new_arr[0] = oom_guard(ft_strdup(token));
		new_arr[1] = NULL;
	}
	else
	{
		arr_size = get_matrix_size(str);
		new_arr = oom_guard(malloc((arr_size + 2) * sizeof(char *)));
		i = -1;
		while (str[++i])
			new_arr[i] = str[i];
		new_arr[i] = oom_guard(ft_strdup(token));
		new_arr[i + 1] = 0;
		free(str);
	}
	return (new_arr);
}
