/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:52:46 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/22 12:50:49 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tree_inorder_traversal(t_node *root, t_env *env);
void exec(t_node *tree, t_env *env);
void run_cmd(t_node node, t_env *env);
void make_redir(t_node node);
void open_pipes(t_node *tree);
void close_pipes(t_node *tree);

void make_pipe_redir(t_node *node);

void execution(t_node *tree, t_env *env)
{
	int pid;

	pid = fork();
	if (!pid)
	{
        open_pipes(tree);
		tree_inorder_traversal(tree, env);
		close_pipes(tree);
		while ((wait(NULL)) > 0);
		exit(0);
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
	make_pipe_redir(node);
	while (node && !is_node_pipe((node)))
	{
		if (is_node_redir(node))
			make_redir(*node);
		if (is_node_cmd(node))
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
		if (!access(path, F_OK | X_OK))
			return (path);
		else
			free(path);
		i++;
	}
	return (0);
}

void run_cmd(t_node node, t_env *env)
{
	char *full_path;
	/*int path_size;
	int cmd_path;
	char *full_path;

	path_size = ft_strlen("/usr/bin/");
	cmd_path = ft_strlen(((t_cmd *)(node.data))->cmd[0]);
	full_path = ft_calloc((path_size + cmd_path + 10), sizeof(char));
	ft_strlcat(full_path, "/usr/bin/", path_size + 1);
	ft_strlcat(full_path, ((t_cmd *)(node.data))->cmd[0], cmd_path + path_size + 1);*/

	full_path = get_cmd_path(((t_cmd *)(node.data))->cmd[0], get_paths(exist_env_elem(env, "PATH")));
	
	execve(full_path, ((t_cmd *)(node.data))->cmd, get_env_matrix(env));
}

void make_redir(t_node node)
{
	int fd;
	char *file;

	file = ((t_redir *)(node.data))->redir;
	if (node.id == ID_IN_REDIR)
	{
		fd = open(file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (node.id == ID_OUT_REDIR)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void make_pipe_redir(t_node *node)
{
	t_node *buff;

	buff = node;
	while (node)
	{
		if (is_node_pipe(node))
		{
			if (node->left == buff)
				dup2(((t_pipe *)(node->data))->w, STDOUT_FILENO);
			else if(node->rigth == buff)
			{
				dup2(((t_pipe *)(node->data))->r, STDIN_FILENO);
				if (node->prev)
					dup2(((t_pipe *)(node->prev->data))->w, STDOUT_FILENO);
			}
			close_pipes(node);
		}
		buff = node;
		node = node->prev;
	}
}

void open_pipes(t_node *tree)
{
	t_pipe *p;
	int	fd_p[2];

	if (tree == NULL) 
		return;
  	open_pipes(tree->left);
	if (is_node_pipe(tree))
	{
		pipe(fd_p);
		p = malloc(sizeof(t_pipe));
		if (!p)
			return ;
		p->r = fd_p[0];
		p->w = fd_p[1];
		tree->data = (void *) p;
	}
}

int get_num_of_pipes(t_node *tree)
{
	int n_pipes;

	n_pipes = 0;
	while (tree)
	{
		if (is_node_pipe(tree))
			n_pipes++;
		tree = tree->left;
	}
	return (n_pipes);
}

void close_pipes(t_node *tree)
{
	t_node *node;

	node = tree;
	while (node)
	{
		if (is_node_pipe(node))
		{
			if (((t_pipe *)(node->data))->w)
			{
				close(((t_pipe *)(node->data))->w);
				((t_pipe *)(node->data))->w = -1;
			}
			if (((t_pipe *)(node->data))->r)
			{
				close(((t_pipe *)(node->data))->r);
				((t_pipe *)(node->data))->r = -1;				
			}
		}			
		node = node->left;
	}
	node = tree;
	while (node)
	{
		if (is_node_pipe(node))
		{
			if (((t_pipe *)(node->data))->w)
			{
				close(((t_pipe *)(node->data))->w);
				((t_pipe *)(node->data))->w = -1;
			}
			if (((t_pipe *)(node->data))->r)
			{
				close(((t_pipe *)(node->data))->r);
				((t_pipe *)(node->data))->r = -1;				
			}
		}	
		node = node->prev;
	}
}
