/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:52:46 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/17 18:09:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tree_inorder_traversal(t_node *root, int n_pipes);
void exec(t_node *tree);
void run_cmd(t_node node);
void make_redir(t_node node);
void open_pipes(t_node *tree);

void execution(t_node *tree)
{   
	int pid;
	int n_pipes;

	pid = fork();
	if (!pid)
	{
		n_pipes = get_num_of_pipes(tree);
		tree_inorder_traversal(tree, n_pipes);
		exit(0);
	}
	wait(&pid);
}

void tree_inorder_traversal(t_node *root, int n_pipes) {
	int pid;

	if (root == NULL) 
		return;
	tree_inorder_traversal(root->left, n_pipes);
	if (!n_pipes || (!is_node_pipe(*root) && is_node_pipe(*(root->prev))))
	{
		pid = fork();
		if (!pid)
		{
			printf("child\n");
			exec(root);
			exit(0);
		}
	}
	tree_inorder_traversal(root->rigth, n_pipes);
}

void exec(t_node *tree)
{
	if (tree == NULL) 
		return;
	exec(tree->left);
	printf("exec\n");
	//run_cmd(*tree);
	
	//executar o que tiver de executar
}

void run_cmd(t_node node)
{
	// Necessita de variáveis de ambiente e verificar se existe comando
	execve("/usr/bin/cat", ((t_cmd *)(node.data))->cmd, NULL);
}

void make_redir(t_node node)
{
	// Vai fazer todas a rediretions antes de correr o commando
}

void open_pipes(t_node *tree)
{
	t_pipe *p;
	int	fd_p[2];

	if (tree == NULL) 
		return;
  	open_pipes(tree->left);
	if (is_node_pipe(*tree))
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
		if (is_node_pipe(*tree))
			n_pipes++;
		tree = tree->left;
	}
	return (n_pipes);
}



