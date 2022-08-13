/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:52:46 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/13 16:14:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exec_cmd_forks(t_node *root, t_env *env, int *l_pid);
static void	exec(t_node *tree, t_env *env);
static void	run_cmd(t_node node, t_env *env);
static t_exit_status	wait_cmds(int n_cmds, int l_pid);

t_exit_status	execution(t_node *tree, t_env *env)
{
	char	**cmd;
	t_exit_status exit_code;
	int		l_pid;

	if (is_builtin_without_pipe(tree))
	{
		hdoc_exec(tree);
		run_builtin_branch(tree, env);
		close_hdoc(tree);
	}
	else
	{
		open_pipes(tree);
		hdoc_exec(tree);
		exec_cmd_forks(tree, env, &l_pid);
		close_pipes(tree);
		close_hdoc(tree);
		exit_code = wait_cmds(get_num_cmds(tree), l_pid);
	}
	return (exit_code);
}

static void	exec_cmd_forks(t_node *root, t_env *env, int *l_pid)
{
	int	pid;

	if (!root)
		return ;
	exec_cmd_forks(root->left, env, l_pid);
	if (root->left == NULL)
	{
		pid = fork();
		if (pid)
		{
			*l_pid = pid;
			//signals_call(SG_IGN);
		}
		if (!(pid))
		{
			//signals_call(SG_DFL);
			config_signal(SIG_DFL);
			exec(root, env);
			exit(0);
		}
	}
	exec_cmd_forks(root->rigth, env, l_pid);
}

static void	exec(t_node *tree, t_env *env)
{
	t_node	*node;

	node = tree;
	pipe_redir(node);
	while (node && !is_node_pipe((node)))
	{
		if (is_node_hdoc(node))
			hdoc_redir(node);
		else if (is_node_redir(node))
			file_redir(*node);
		else if (is_node_cmd(node))
			run_cmd(*node, env);
		node = node->prev;
	}
}

static void	run_cmd(t_node node, t_env *env)
{
	char	*full_path;
	char	**cmd;

	cmd = ((t_cmd *)(node.data))->cmd;
	if (is_builtin(cmd[0]))
		exec_builtin(cmd, env, STDOUT_FILENO);
	else
	{
		full_path = get_cmd_path(cmd[0], env);
		execve(full_path, cmd, get_env_matrix(env));
	}
}

static t_exit_status	wait_cmds(int n_cmds, int l_pid)
{
	int	status;
	t_exit_status	exit;

	if (waitpid(l_pid, &status, 0))
	{
		if (WIFEXITED(status))
			exit.code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			exit.code = status + EXIT_FATAL_SIGNAL;
			// Ter em atenção o e verificar como funciona para outro sinais
			// pode precisar da verificação se é sinal CTRL-C
			exit.signal = 1;	
		}
	}
	n_cmds--;
	while (n_cmds)
	{
		wait(&status);
		if (WIFSIGNALED(status))
			exit.signal = 1;
		n_cmds--;
	}
	return (exit);
}
