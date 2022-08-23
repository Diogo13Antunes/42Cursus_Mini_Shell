/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/23 15:28:44 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h> 


int main (int argc, char **argv, char **env)
{
    char *str;
    t_node *tree;
	t_env	*env_lst;
	char *prompt;
    int exit_code;
    t_exit_status ex;

    init_alloc_mem();
    set_signal(SIGQUIT, SIG_IGN);
    exit_code = 0;
	env_lst = get_env_list(env);
    save_alloc_mem(env_lst, TYPE_ENV);
    while (1)
    {
        set_signal(SIGINT, new_prompt_handler);
	    prompt = get_prompt_str(env_lst);
        str = readline(prompt);
        if (!str)
            builtin_exit();
        set_signal(SIGINT, SIG_IGN);
        if (str && str[0])
            add_history(str);
		free(prompt);
        exit_code = get_exit_status();
        tree = parser(str, env_lst, &exit_code);
        save_alloc_mem(tree, TYPE_TREE);
        free(str);
        if (tree)
        {
            clear_exit_status();
            execution(tree, env_lst);
            exit_code = get_exit_status();
            free_tree(tree);
        }
    }
    free_alloc_mem();
    
    //teste para verificar se a tree é corretamente limpa 
    //tree = parser("<in ls -la | cat | wc -l >out", NULL, exit_code);
    //print2D(tree);
    //free_tree(tree);

    return (0);
}



// teste free memory
/*
int main (int argc, char **argv, char **env)
{
    char *str;
    t_node *tree;
	t_env	*env_lst;
	char *prompt;
    int exit_code;
    t_exit_status ex;

    init_alloc_mem();

    set_signal(SIGQUIT, SIG_IGN);
    exit_code = 0;
	env_lst = get_env_list(env);
    save_alloc_mem(env_lst, TYPE_ENV);


    str = ft_calloc(sizeof(char), 100);
    ft_strcat(str, "env | grep HOME");


    //set_signal(SIGINT, new_prompt_handler);
    //prompt = get_prompt_str(env_lst);
    //str = readline(prompt);
    //if (!str)
        //builtin_exit();
    //set_signal(SIGINT, SIG_IGN);
    //if (str && str[0])
    //    add_history(str);
    //free(prompt);
    exit_code = get_exit_status();
    tree = parser(str, env_lst, &exit_code);
    save_alloc_mem(tree, TYPE_TREE);
    free(str);
    if (tree)
    {
        clear_exit_status();
        execution(tree, env_lst);
        exit_code = get_exit_status();
        //free_tree(tree);
    }
    //free_env_lst(env_lst);

    free_alloc_mem();

   // --leak-check=full
   // --leak-check=full --show-leak-kinds=all
    return (0);
}
*/


