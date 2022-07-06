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

void execution(t_node *tree, t_env *env)
{
	int pid;
	char **cmd;

	pid = fork();
	if (!pid)
	{
		// TESTE CD
		if (is_node_cmd(tree) && !ft_memcmp(((t_cmd *)(tree->data))->cmd[0], "cd", 3))
		{
			cmd = ((t_cmd *)(tree->data))->cmd;
			builtin_cd(cmd, env);
		}
		else if (is_node_cmd(tree) && !ft_memcmp(((t_cmd *)(tree->data))->cmd[0], "export", 7))
		{
			cmd = ((t_cmd *)(tree->data))->cmd;
			builtin_export(env, cmd, STDOUT_FILENO);
		}
		else if (is_node_cmd(tree) && !ft_memcmp(((t_cmd *)(tree->data))->cmd[0], "unset", 6))
		{
			cmd = ((t_cmd *)(tree->data))->cmd;
			builtin_unset(&env, cmd);
		}
		else
		{
			open_pipes(tree);
			hdoc_exec(tree);
			// percorre toda a tree para depois executar os comandos fazer diferente
			tree_inorder_traversal(tree, env);
			close_pipes(tree);
			hdoc_close(tree);
			while ((wait(NULL)) > 0);
			exit(0);	
		}
	}
	waitpid(pid, NULL, 0);
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
		if (node->id == ID_IN_HERDOC)
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
		{
			
			ft_strcat(path, cmd);
			//ft_putstr_fd("DEVIA DAR ERRO EXECUÇAO\n", STDERR_FILENO);
			//file_error(access(path, X_OK), cmd);
			//file_error(stat(path, &path_stat), cmd);
			//S_ISREG(path_stat.st_mode)
		}
		else
		{
			ft_strcat(path, paths[i]);
			ft_strcat(path, "/");
			ft_strcat(path, cmd);
		}
		/*if (!access(path, F_OK | X_OK))
			return (path);
		else
			free(path);*/
		if (!access(path, F_OK))
		{
			//file_error(access(path, X_OK), cmd);
				//file_error(int err, char *file)
			return (path);
		}
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

void run_cmd(t_node node, t_env *env)
{
	char *full_path;
	char **cmd;
	
	cmd = ((t_cmd *)(node.data))->cmd;
	if (!ft_memcmp(cmd[0], "echo", ft_strlen("echo") + 1))
		builtin_echo(cmd, STDOUT_FILENO);
	else if (!ft_memcmp(cmd[0], "env", ft_strlen("env") + 1))
		builtin_env(*env, STDOUT_FILENO);
	else if (!ft_memcmp(cmd[0], "pwd", ft_strlen("pwd") + 1))
		builtin_pwd(STDOUT_FILENO);
	else
	{
		full_path = get_cmd_path(cmd[0], get_paths(exist_env_elem(env, "PATH")));
		//cmd_not_found_error(full_path, cmd[0]);
		check_path(full_path, cmd[0]);
		execve(full_path, cmd, get_env_matrix(env));
	}
}
