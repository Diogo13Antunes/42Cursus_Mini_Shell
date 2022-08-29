/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/29 17:32:19 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h> 

//valgrind --leak-check=full --show-leak-kinds=all  ./minishell

int	main(int argc, char **argv, char **env)
{
	char			*str;
	t_node			*tree;
	t_env			*env_lst;
	char			*prompt;
	int				exit_code;
	t_exit_status	ex;

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
		{
			free_str(prompt);
			builtin_exit();
		}
		set_signal(SIGINT, SIG_IGN);
		if (str && str[0])
			add_history(str);
		free_str(prompt);
		exit_code = get_exit_status();
		tree = parser(str, env_lst, &exit_code);
		save_alloc_mem(tree, TYPE_TREE);
		free_str(str);
		if (tree)
		{
			clear_exit_status();
			execution(tree, env_lst);
			exit_code = get_exit_status();
			free_tree(tree);
			save_alloc_mem(NULL, TYPE_TREE);
		}
	}
	free_all_alloc_mem();
	return (0);
}
