/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:57:02 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/27 11:26:27 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_redir(t_node node)
{
	int		fd;
	int		fd2;
	int		flag;
	char	*file;

	file = ((t_redir *)(node.data))->redir;
	if (node.id == ID_IN_REDIR)
	{
		fd2 = STDIN_FILENO;
		flag = O_RDONLY;
	}
	else
	{
		fd2 = STDOUT_FILENO;
		if (node.id == ID_OUT_REDIR)
			flag = O_CREAT | O_WRONLY | O_TRUNC;
		else if (node.id == ID_OUT_APPEND)
			flag = O_CREAT | O_WRONLY | O_APPEND;
	}
	fd = file_error(open(file, flag, 0644), file);
	dup2(fd, fd2);
	close(fd);
}

/*
void	heredoc_redir(t_node node)
{
	t_redir	*redir;
	t_pipe	p;
	char	*str;

	p = open_pipe();
	redir = ((t_redir *)(node.data));
	while (1)
	{
		str = readline("heredoc> ");
		if (!ft_strcmp(redir->redir, str))
			break ;
		ft_putstr_fd(str, p.w);
		ft_putstr_fd("\n", p.w);
		free(str);
	}
	free(str);
	dup2(p.r, STDIN_FILENO);
	close_pipe(p);
}
*/

void	pipe_redir(t_node *node)
{
	t_node	*buff;
	t_pipe	*p;

	buff = node;
	while (node)
	{
		if (is_node_pipe(node))
		{
			p = (t_pipe *)(node->data);
			if (node->left == buff)
				dup2(p->w, STDOUT_FILENO);
			else if (node->rigth == buff)
			{
				dup2(p->r, STDIN_FILENO);
				if (node->prev)
				{
					p = (t_pipe *)(node->prev->data);
					dup2(p->w, STDOUT_FILENO);
				}
			}
			close_pipes(node);
		}
		buff = node;
		node = node->prev;
	}
}
