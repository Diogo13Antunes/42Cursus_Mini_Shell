/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/12 15:18:39 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
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
        signals_call(SG_RDL);
	    prompt = get_prompt_str(env_lst);
        str = readline(prompt);
        signals_call(SG_IGN);
        if (str && str[0])
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