/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/22 11:53:21 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void test_parser(char *src);

int main (int argc, char **argv, char **env)
{
    char *str;
    t_node *tree;
	t_env	*env_lst;

	env_lst = get_env_list(env);
	//builtin_env(*env_lst, STDOUT_FILENO);
    while (1)
    {
        str = readline("minishell > ");
        //test_parser(str);
        tree = parser(str);
        
        //open_pipes(tree);
	    //execution(tree, env);
        print2D(tree);
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