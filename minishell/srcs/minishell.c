/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/13 17:52:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h> 

static void test_parser(char *src);


// criar um modulo que guarda o exit_status numa variável estática
// save_exit_status(int code)
// clean_exit_status(void)
// int get_exit_status()
int exit_status(int code, int op)
{
    static int status_code = 0;
    int buff;

    if (op == 1)
        status_code = code;
    else if (op == 2)
    {
        buff = status_code; 
        status_code = 0;
        return (buff);
    }
    return (status_code);
}

void get_new_prompt(int signum)
{
    if (signum == SIGINT)
    {
        //rl_replace_line("", 0);
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
        rl_redisplay();
        exit_status(EXIT_CTRLC_SIGNAL, 1);
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

    exit_code = 0;
	env_lst = get_env_list(env);
    while (1)
    {
        //signals_call(SG_RDL);
        config_signal(get_new_prompt);
	    prompt = get_prompt_str(env_lst);
        str = readline(prompt);
        if (exit_status(0, 0))
           exit_code = exit_status(0, 2);
        config_signal(SIG_IGN);
        //signals_call(SG_IGN);
        if (str && str[0])
            add_history(str);
		free(prompt);
        tree = parser(str, env_lst, &exit_code);
        free(str);
        if (tree)
        {
           ex = execution(tree, env_lst);
           exit_code = ex.code;
        }
        if (ex.signal)
            ft_putstr_fd("\n", STDOUT_FILENO);
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
