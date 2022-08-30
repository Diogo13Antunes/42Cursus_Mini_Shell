/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:42:18 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/30 11:55:24 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h> 

//valgrind --leak-check=full --show-leak-kinds=all  ./minishell

static char	*get_user_input(t_env *env_lst);
static void	*executor(char *str, t_env *env_lst, int *exit_code);
static int	check_void_input(char *input);

int	main(int argc, char **argv, char **env)
{
	char			*str;
	t_env			*env_lst;
	int				exit_code;

	init_alloc_mem();
	set_signal(SIGQUIT, SIG_IGN);
	exit_code = 0;
	env_lst = get_env_list(env);
	save_alloc_mem(env_lst, TYPE_ENV);
	while (1)
	{
		set_signal(SIGINT, new_prompt_handler);
		str = get_user_input(env_lst);
		set_signal(SIGINT, SIG_IGN);
		exit_code = get_exit_status();
		executor(str, env_lst, &exit_code);
	}
	free_all_alloc_mem();
	return (0);
}

static void	*executor(char *str, t_env *env_lst, int *exit_code)
{
	t_node	*tree;

	tree = parser(str, env_lst);
	save_alloc_mem(tree, TYPE_TREE);
	free_str(str);
	if (tree)
	{
		clear_exit_status();
		execution(tree, env_lst);
		*exit_code = get_exit_status();
		free_tree(tree);
		save_alloc_mem(NULL, TYPE_TREE);
	}
}

static char	*get_user_input(t_env *env_lst)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt_str(env_lst);
	input = readline(prompt);
	free_str(prompt);
	if (!input)
		builtin_exit();
	else if (input && !check_void_input(input))
		add_history(input);
	return (input);
}

static int	check_void_input(char *input)
{
	int	i;
	int	count_spaces;
	int	input_len;

	input_len = (int)ft_strlen(input);
	if (!input_len)
		return (1);
	i = 0;
	count_spaces = 0;
	while (input[i])
	{
		if (input[i] < 33 || input[i] == 127)
			count_spaces++;
		i++;
	}
	if (count_spaces == input_len)
		return (1);
	return (0);
}
