/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/17 11:27:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h> 

static void test_parser(char *src);

void get_new_prompt(int signum)
{
    if (signum == SIGINT)
    {
        rl_replace_line("", 0);
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
        rl_redisplay();
        set_exit_status(EXIT_CTRLC_SIGNAL);
    }
}

int main (int argc, char **argv, char **env)
{
    char *str;
    t_node *tree;
	t_env	*env_lst;
	char *prompt;
    int exit_code;
    t_exit_status ex;

    config_signal(SIGQUIT, SIG_IGN);
    exit_code = 0;
	env_lst = get_env_list(env);
    while (1)
    {
        config_signal(SIGINT, get_new_prompt);
	    prompt = get_prompt_str(env_lst);
        str = readline(prompt);
        config_signal(SIGINT, SIG_IGN);
        if (str && str[0])
            add_history(str);
		free(prompt);
        exit_code = get_exit_status();
        tree = parser(str, env_lst, &exit_code);
        free(str);
        if (tree)
        {
            clear_exit_status();
            execution(tree, env_lst);
            exit_code = get_exit_status();
        }
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
