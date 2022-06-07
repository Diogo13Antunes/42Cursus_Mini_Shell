/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:06 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/07 19:19:18 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_new_redir(t_node **tree, t_node *node);

t_node  *create_node(int id)
{
    t_node *node;

    node = malloc(sizeof(t_node));
    if (!node)
        return (0);
    node->id = id;
    node->data = NULL;
    node->prev = NULL;
    node->left = NULL;
    node->rigth = NULL;
    return (node);
}

void add_new_node(t_node **tree, t_node *node)
{
    if (is_node_redir(*node))
        add_new_redir(tree, node);
}

void add_new_redir(t_node **tree, t_node *node)
{
    t_node *first;

    first = *tree;
    if (!first)
        first = node;
    else if (first && is_node_redir(*first))
    {
        node->left = first;
        first = node;
    }
    // Se o primeiro for comando: coloca-se a seguir ao comando  
    // Se o primeiro for pipe: desce pela direita até ao comando e coloca-se a seguir ao comando
    *tree = first;
}

void add_new_cmd(t_node **tree, t_node *node)
{
    t_node *first;
    
    first = *tree;
    *tree = first;
}