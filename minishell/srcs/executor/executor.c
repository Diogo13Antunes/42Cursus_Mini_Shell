/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:52:46 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/26 15:58:12 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_main_fork(t_node *tree, t_env *env);
static void	exec_cmds(t_node *root, t_env *env, int *l_pid);
static void	exec_cmd_brunch(t_node *tree, t_env *env);
static void	run_cmd(t_node node, t_env *env);

void	execution(t_node *tree, t_env *env)
{
	int	pid;
	int	status;
	int	exit_code;

	pid = fork();
	if(pid == -1)
		print_msg_error(strerror(errno), "fork");
	if (!pid)
		exec_main_fork(tree, env);
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

static void	exec_main_fork(t_node *tree, t_env *env)
{
	int	last_pid;
	int	hdoc_error;

	set_signal(SIGINT, hdoc_interrupt_handler);
	hdoc_error = hdoc_exec(tree);
	set_signal(SIGINT, SIG_IGN);
	if (hdoc_error != HDOC_SUCCESS)
	{
		close_hdoc(tree);
		if (!is_builtin_without_pipe(tree))
			ft_exit(get_exit_status());
		else
			ft_exit(hdoc_error);
	}
	else if (!is_builtin_without_pipe(tree))
	{
		open_pipes(tree);
		exec_cmds(tree, env, &last_pid);
		close_pipes(tree);
		close_hdoc(tree);
		wait_cmds(last_pid, get_num_cmds(tree));
		ft_exit(get_exit_status());
	}
	//ft_exit(HDOC_SUCCESS);
	ft_exit(get_exit_status());
}

static void	exec_cmds(t_node *root, t_env *env, int *l_pid)
{
	int	pid;

	if (!root)
		return ;
	exec_cmds(root->left, env, l_pid);
	if (root->left == NULL)
	{
		pid = fork();
		if (pid)
			*l_pid = pid;
		if (!(pid))
			exec_cmd_brunch(root, env);
	}
	exec_cmds(root->rigth, env, l_pid);
}

static void	exec_cmd_brunch(t_node *tree, t_env *env)
{
	t_node	*node;

	node = tree;
	//ft_putstr_fd("pipe_redir\n", STDERR_FILENO);
	pipe_redir(node);
	set_signal(SIGINT, SIG_DFL);
	set_signal(SIGQUIT, SIG_DFL);
	while (node && !is_node_pipe((node)))
	{
		if (is_node_hdoc(node))
			hdoc_redir(node);
		else if (is_node_redir(node))
			file_redir(*node);
		else if (is_node_cmd(node))
		{
			close_hdoc(node);
			run_cmd(*node, env);
		}
		node = node->prev;
	}
	close_hdoc(tree);
	//ft_exit(EXIT_SUCCESS);
	ft_exit(get_exit_status());
}

static void	run_cmd(t_node node, t_env *env)
{
	char	*full_path;
	char	**cmd;

	cmd = ((t_cmd *)(node.data))->cmd;
	if (is_builtin(cmd[0]))
	{
		if (ft_strcmp("exit", cmd[0]))
			exec_builtin(cmd, env, STDOUT_FILENO);
	}	
	else
	{
		full_path = get_cmd_path(cmd[0], env);
		execve(full_path, cmd, get_env_matrix(env));
	}
}
