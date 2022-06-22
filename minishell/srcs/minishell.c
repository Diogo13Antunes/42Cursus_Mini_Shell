/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/22 14:51:59 by dcandeia         ###   ########.fr       */
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

	env_lst = get_env_list(env);
    while (1)
    {
		prompt = get_prompt_str(env_lst);
        str = readline(prompt);
		free(prompt);
		
        //test_parser(str);
        tree = parser(str);
        
        //open_pipes(tree);
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