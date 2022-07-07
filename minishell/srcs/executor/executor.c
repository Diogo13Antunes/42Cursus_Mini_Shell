/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:52:46 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/23 16:11:23 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tree_inorder_traversal(t_node *root, t_env *env);
void exec(t_node *tree, t_env *env);
void run_cmd(t_node node, t_env *env);


int is_builtin_to_run(t_node *tree);
void exec_builtins3(t_node *tree, t_env *env);

void execution(t_node *tree, t_env *env)
{
	char **cmd;

	if(is_builtin_to_run(tree))
	{
		hdoc_exec(tree);
		exec_builtins3(tree, env);
		hdoc_close(tree);
	}
	else
	{
		open_pipes(tree);
		hdoc_exec(tree);
		tree_inorder_traversal(tree, env);
		close_pipes(tree);
		hdoc_close(tree);
	}
	while ((wait(NULL)) > 0);
}

void tree_inorder_traversal(t_node *root, t_env *env) 
{
	int pid;

	if (root == NULL) 
		return;
	tree_inorder_traversal(root->left, env);
	if (root->left == NULL)
	{
		pid = fork();
		if (!pid)
		{
			exec(root, env);
			exit(0);
		}
	}
	tree_inorder_traversal(root->rigth, env);
}

void exec(t_node *tree, t_env *env)
{
	t_node *node;
	
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

char **get_paths(t_env *path)
{
	char **paths;

	if (!path)
		return (NULL);
	paths = ft_split(path->content, ':');
	return(paths);
}

static int	is_cmd_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*path;
	int		size;
	int		i;

	struct stat path_stat;

	i = 0;
	while (paths[i])
	{
		size = ft_strlen(paths[i]) + ft_strlen(cmd) + 1;
		path = ft_calloc(size + 1, sizeof(char));
		if (is_cmd_path(cmd))
			ft_strcat(path, cmd);
		else
		{
			ft_strcat(path, paths[i]);
			ft_strcat(path, "/");
			ft_strcat(path, cmd);
		}
		if (!access(path, F_OK))
			return (path);
		else
			free(path);
		i++;
	}
	return (0);
}

static void check_path(char *path, char *cmd)
{
	struct stat path_stat;
	int err;

	cmd_not_found_error(path, cmd);
	err = access(path, X_OK);
	if(err)
	{
		free(path);
		file_error(err, cmd);
	}
	err = stat(path, &path_stat);
	if(err)
	{
		free(path);
		file_error(err, cmd);
	}
	err = S_ISREG(path_stat.st_mode);
	if (!err)
	{
		free(path);
		print_msg_error("Is a directory", cmd);
	}
}

int is_builtins(char *cmd)
{
	if (!ft_strcmp("echo", cmd)
		|| !ft_strcmp("env", cmd)
		|| !ft_strcmp("pwd", cmd)
		|| !ft_strcmp("cd", cmd)
		|| !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd))
		return(1);
	return (0);
}

int is_builtins2(char *cmd)
{
	if (!ft_strcmp("cd", cmd)
		|| !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd))
		return(1);
	return (0);
}

void exec_builtins(char **cmd, t_env *env)
{
	if (!ft_strcmp("echo", cmd[0]))
		builtin_echo(cmd, STDOUT_FILENO);
	else if (!ft_strcmp("env", cmd[0]))
		builtin_env(*env, STDOUT_FILENO);
	else if (!ft_strcmp("pwd", cmd[0]))
		builtin_pwd(STDOUT_FILENO);
}

void exec_builtins2(char **cmd, t_env *env)
{
	if (!ft_strcmp("cd", cmd[0]))
		builtin_cd(cmd, env);
	else if (!ft_strcmp("export", cmd[0]))
		builtin_export(env, cmd, STDOUT_FILENO);
	else if (!ft_strcmp("unset", cmd[0]))
		builtin_unset(&env, cmd);
}

void exec_builtins4(t_node *tree, t_env *env)
{
	int err;
	t_node *node;

	node = tree;

	while (node)
	{
		if (is_node_cmd(node))
		{
			exec_builtins2(((t_cmd *)node->data)->cmd, env);
		}
		else if (is_node_redir(node) && !is_node_hdoc(node))
		{
			if (file_redir2(*node) < 0)
				return ;
		}
		node = node->prev;
	}
}


void exec_builtins3(t_node *tree, t_env *env)
{
	if (tree == NULL) 
		return ;
	exec_builtins3(tree->left, env);
	if (tree->left == NULL)
	{
		exec_builtins4(tree, env);
	}

	/*
	if (is_node_cmd(tree))
		exec_builtins2(((t_cmd *)tree->data)->cmd, env);
	else if (is_node_redir(tree) && !is_node_hdoc(tree))
		file_redir2(*tree);
	*/
}

// verifica se tem o comando pretendido para correr
int is_builtin_to_run(t_node *tree)
{
	t_node *node;
	char	**cmd;

	if (is_node_pipe(tree))
		return (0);
	node = tree;
	while (node)
	{
		if (is_node_cmd(node))
		{
			cmd = ((t_cmd *) node->data)->cmd;
			if (is_builtins2(cmd[0]))
				return (1);
		}	
		node = node->left;
	}
	return (0);
}

void run_cmd(t_node node, t_env *env)
{
	char *full_path;
	char **cmd;
	
	cmd = ((t_cmd *)(node.data))->cmd;
	if (is_builtins(cmd[0]))
		exec_builtins(cmd, env);
	else 
	{
		full_path = get_cmd_path(cmd[0], get_paths(exist_env_elem(env, "PATH")));
		check_path(full_path, cmd[0]);
		execve(full_path, cmd, get_env_matrix(env));		
	}
}


