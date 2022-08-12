/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:14:42 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:04 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	run_builtin_branch2(t_node *tree, t_env *env);

int	is_builtin(char *cmd)
{
	if (!ft_strcmp("echo", cmd)
		|| !ft_strcmp("env", cmd)
		|| !ft_strcmp("pwd", cmd)
		|| !ft_strcmp("cd", cmd)
		|| !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd)
		|| !ft_strcmp("exit", cmd))
		return (1);
	return (0);
}

int	is_builtin_without_pipe(t_node *tree)
{
	t_node	*node;
	char	**cmd;

	if (is_node_pipe(tree))
		return (0);
	node = tree;
	while (node)
	{
		if (is_node_cmd(node))
		{
			cmd = ((t_cmd *) node->data)->cmd;
			if (is_builtin(cmd[0]))
				return (1);
		}
		node = node->left;
	}
	return (0);
}

void	exec_builtin(char **cmd, t_env *env, int fd)
{
	if (!ft_strcmp("cd", cmd[0]))
		builtin_cd(cmd, env);
	else if (!ft_strcmp("export", cmd[0]))
		builtin_export(env, cmd, fd);
	else if (!ft_strcmp("unset", cmd[0]))
		builtin_unset(&env, cmd);
	else if (!ft_strcmp("exit", cmd[0]))
		builtin_exit();
	else if (!ft_strcmp("echo", cmd[0]))
		builtin_echo(cmd, fd);
	else if (!ft_strcmp("env", cmd[0]))
		builtin_env(*env, fd);
	else if (!ft_strcmp("pwd", cmd[0]))
		builtin_pwd(fd);
}

void	run_builtin_branch(t_node *tree, t_env *env)
{
	if (tree == NULL)
		return ;
	run_builtin_branch(tree->left, env);
	if (tree->left == NULL)
		run_builtin_branch2(tree, env);
}

static void	run_builtin_branch2(t_node *tree, t_env *env)
{
	t_node	*node;
	int		err;
	int		fd;

	fd = -1;
	node = tree;
	while (node)
	{
		if (is_node_cmd(node))
		{
			if (fd > -1)
				exec_builtin(((t_cmd *)node->data)->cmd, env, fd);
			else
				exec_builtin(((t_cmd *)node->data)->cmd, env, STDOUT_FILENO);
		}
		else if (is_node_redir(node) && !is_node_hdoc(node))
		{
			close_fd(fd);
			fd = get_file_fd(*node);
			if (fd < 0)
				return ;
		}
		node = node->prev;
	}
	close_fd(fd);
}
