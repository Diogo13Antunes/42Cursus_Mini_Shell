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


/*void control_c(int sig)
{
   // printf("enviado sinal control C\n");
}*/

int main (int argc, char **argv, char **env)
{
    char *str;
    t_node *tree;
	t_env	*env_lst;
	char *prompt;
    int exit_code;

    /*struct sigaction sa;
    sa.sa_handler = &control_c;
    //sa.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sa, NULL);*/


    int i = 0;
    exit_code = 0;
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
        tree = parser(str, env_lst, exit_code);
        free(str);

        // is_syntax_error tem de ser colocado no parser
        // Aqui a verificação tem de ser se a tree é !NULL então executa os comandos
        /*if(!is_syntax_error(tree))
            execution(tree, env_lst);*/
        if (tree)
           exit_code = execution(tree, env_lst);
        
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