/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:52:46 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/21 17:38:10 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd_forks(t_node *root, t_env *env, int *l_pid);
static void	exec(t_node *tree, t_env *env);
static void	run_cmd(t_node node, t_env *env);


void interrupt_hdoc_signal(int signum)
{
    if (signum == SIGINT)
    {
		close(STDIN_FILENO);
		set_exit_status(EXIT_CTRLC_SIGNAL);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int convert_hdoc_stop_code(int code)
{
	if (code == HDOC_STOP_CTRL_C)
		return (EXIT_CTRLC_SIGNAL);
	else
		return (EXIT_SUCCESS);
}

void main_fork_exec(t_node *tree, t_env *env)
{
	int	last_pid;
	int hdoc_error;

	config_signal(SIGINT, interrupt_hdoc_signal);
	hdoc_error = hdoc_exec(tree);
	config_signal(SIGINT, SIG_IGN);
	if (hdoc_error != HDOC_SUCCESS)
	{
		if (!is_builtin_without_pipe(tree))
			exit(get_exit_status());
		else 
			exit(hdoc_error);
	}
	else if (!is_builtin_without_pipe(tree))
	{
		open_pipes(tree);
		exec_cmd_forks(tree, env, &last_pid);
		close_pipes(tree);
		close_hdoc(tree);
		//wait_cmds(get_num_cmds(tree), last_pid);
		wait_cmds(last_pid, get_num_cmds(tree));
		exit(get_exit_status());
	}
	exit(HDOC_SUCCESS);
}

void	execution(t_node *tree, t_env *env)
{
	int	pid;
	int status;
	int exit_code;

	pid = fork();
	if (!pid)
		main_fork_exec(tree, env);
	else
	{
		wait(&status);
		exit_code = WEXITSTATUS(status);
		if (is_builtin_without_pipe(tree) && exit_code != HDOC_SUCCESS)
			set_exit_status(convert_hdoc_stop_code(exit_code));
		else if (is_builtin_without_pipe(tree) && exit_code == HDOC_SUCCESS)
			run_builtin_branch(tree, env);
		else
			set_exit_status(exit_code);
	}
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
			*l_pid = pid;
		if (!(pid))
		{
			config_signal(SIGINT, SIG_DFL);
			config_signal(SIGQUIT, SIG_DFL);
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
