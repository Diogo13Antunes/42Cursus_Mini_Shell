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

int main (int argc, char **argv, char **env)
{
    char *str;
    t_node *tree;
	t_env	*env_lst;
	char *prompt;

    int i = 0;
	env_lst = get_env_list(env);
    while (1)
    {
		prompt = get_prompt_str(env_lst);
        str = readline(prompt);
       /*
        if (str)
            add_history(str);
        tree = parser(str, env_lst);
        print2D(tree);
        */
        
        if (str)
            add_history(str);

		free(prompt);		
        tree = parser(str, env_lst);
        free(str);

        // is_syntax_error tem de ser colocado no parser
        // Aqui a verificação tem de ser se a tree é !NULL então executa os comandos
        /*if(!is_syntax_error(tree))
            execution(tree, env_lst);*/
        if (tree)
            execution(tree, env_lst);
        
        //print2D(tree);   
        
    }
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