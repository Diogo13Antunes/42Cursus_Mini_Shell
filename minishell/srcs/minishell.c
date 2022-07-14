/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/09 20:11:18 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h> 

static void test_parser(char *src);


int main (int argc, char **argv, char **env)
{
    char *str;
    t_node *tree;
	t_env	*env_lst;
	char *prompt;
    int exit_code;

    exit_code = 0;
	env_lst = get_env_list(env);
    while (1)
    {
	    prompt = get_prompt_str(env_lst);
        str = readline(prompt);
        if (str)
            add_history(str);
		free(prompt);		
        tree = parser(str, env_lst, &exit_code);
        free(str);
        if (tree)
           exit_code = execution(tree, env_lst);
        free_tree(tree);   
        //print2D(tree);
    }

    /*
    //teste para verificar se a tree é corretamente limpa 
    tree = parser("<in ls -la | cat | wc -l >out", NULL, exit_code);
    print2D(tree);
    free_tree(tree);
    */

    return (0);
}

/*
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
*/