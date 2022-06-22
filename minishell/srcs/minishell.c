/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/22 17:10:07 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void test_parser(char *src);

void print_token(t_node *node)
{
	if (node->id == ID_IN_REDIR)
	    ft_putstr_fd("\'<\'\n", STDERR_FILENO); 
	else if (node->id == ID_OUT_REDIR)
	    ft_putstr_fd("\'>\'\n", STDERR_FILENO);
	else if (node->id == ID_OUT_HERDOC)
	    ft_putstr_fd("\'>>\'\n", STDERR_FILENO);
	else if (node->id == ID_IN_HERDOC)
	    ft_putstr_fd("\'<<\'\n", STDERR_FILENO);
    else if (node->id == ID_PIPE)
	    ft_putstr_fd("\'|\'\n", STDERR_FILENO);
}

void tree_traversal(t_node *node, t_node **node_err, int *error) 
{
	if (node == NULL) 
		return ;
	tree_traversal(node->left, node_err, error);
    if (is_node_redir(node))
    {
        if (!(node->data))
        {
            *error = 1;
            if (!(*node_err))
                *node_err = node;
        }
    }
	tree_traversal(node->rigth, node_err, error);
}

int is_syntax_error(t_node *tree)
{
    t_node *node_err;
    int error;

    error = 0;
    node_err = NULL;
    tree_traversal(tree, &node_err, &error);
    if (error)
    {
        // ls > | neste caso assume o pipe como comando 'e um erro no parse.
        printf("id:  %i \n", node_err->prev->id); 
        ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
        if (node_err->prev) 
            print_token(node_err->prev);
        return (1);
    }
    return (0);
}

int main (int argc, char **argv, char **env)
{
    char *str;
    t_node *tree;
	t_env	*env_lst;
	char *prompt;

	env_lst = get_env_list(env);
    while (1)
    {
		prompt = get_prompt_str(env_lst);
        str = readline(prompt);
		free(prompt);
		
        tree = parser(str);
        if(!is_syntax_error(tree))
            execution(tree, env_lst);
        //print2D(tree);
        free(str);
    }
    return (0);
}

static void test_parser(char *src)
{
    char *str;

    if (!src)
    {
        printf("nothing to parse\n");
        return ;
    }
    str = get_next_token(src);
    while (str)
    {
        printf("%s\n",str);
        str = get_next_token(src);
    }
	return ;
}