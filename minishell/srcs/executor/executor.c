/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:52:46 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/19 11:20:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd_forks(t_node *root, t_env *env, int *l_pid);
static void	exec(t_node *tree, t_env *env);
static void	run_cmd(t_node node, t_env *env);
static t_exit_status	wait_cmds(int n_cmds, int l_pid);

void interrupt_hdoc_signal(int signum)
{
    if (signum == SIGINT)
    {
		close(STDIN_FILENO);
		set_exit_status(EXIT_CTRLC_SIGNAL);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int	execution(t_node *tree, t_env *env)
{
	char	**cmd;
	int		l_pid;
	int 	pid;
	int status;
	int exit_code;

	if (is_builtin_without_pipe(tree))
	{
		pid = fork();
		if (!pid)
		{
			config_signal(SIGINT ,interrupt_hdoc_signal);
			hdoc_exec(tree);
			config_signal(SIGINT, SIG_IGN);
			close_hdoc(tree);
			exit(1);
		}
		else 
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
				if (exit_code == 1 || exit_code == 0)
					set_exit_status(0);
				else 
					set_exit_status(exit_code);
			}
			if (exit_code == 1)
				run_builtin_branch(tree, env);
		}
	}
	else
	{
		pid = fork();
		if (!pid)
		{
			config_signal(SIGINT, interrupt_hdoc_signal);
			hdoc_exec(tree);
			config_signal(SIGINT, SIG_IGN);
			if (get_exit_status() == EXIT_CTRLC_SIGNAL)
			{
				close_hdoc(tree);
				exit(get_exit_status());
			}
			open_pipes(tree);
			exec_cmd_forks(tree, env, &l_pid);
			close_pipes(tree);
			close_hdoc(tree);
			wait_cmds(get_num_cmds(tree), l_pid);
			exit(get_exit_status());
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				set_exit_status(WEXITSTATUS(status));
		}
	}
	return (get_exit_status());
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

static t_exit_status	wait_cmds(int n_cmds, int l_pid)
{
	int	status;
	int signal;
	t_exit_status	exit;

	signal = 0;
	if (waitpid(l_pid, &status, 0))
	{
		if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status));
		if (WIFSIGNALED(status))
		{
			if (status < 130)
			{
				set_exit_status(status + EXIT_FATAL_SIGNAL);
				signal = 1;
			}	
			else
			{
				ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
				set_exit_status(status);
			}
		}
	}
	n_cmds--;
	while (n_cmds)
	{
		wait(&status);
		if (WIFSIGNALED(status) && status < 130)
			signal = 1;
		n_cmds--;
	}
	if (signal)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (exit);
}
