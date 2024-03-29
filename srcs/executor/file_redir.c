/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:57:02 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/27 17:21:06 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_redir(t_node node)
{
	int		file_fd;
	int		std_fd;
	int		flag;
	char	*file;

	file = ((t_redir *)(node.data))->redir;
	if (node.id == ID_IN_REDIR)
	{
		std_fd = STDIN_FILENO;
		flag = O_RDONLY;
	}
	else
	{
		std_fd = STDOUT_FILENO;
		if (node.id == ID_OUT_REDIR)
			flag = O_CREAT | O_WRONLY | O_TRUNC;
		else if (node.id == ID_OUT_APPEND)
			flag = O_CREAT | O_WRONLY | O_APPEND;
	}
	file_fd = sys_error(open(file, flag, 0644), file);
	sys_error(dup2(file_fd, std_fd), "dup2");
	sys_error(close(file_fd), "close");
}

int	get_file_fd(t_node node)
{
	int		fd;
	int		flag;
	char	*file;

	fd = -1;
	file = ((t_redir *)(node.data))->redir;
	if (node.id == ID_IN_REDIR)
		flag = O_RDONLY;
	else if (node.id == ID_OUT_REDIR)
		flag = O_CREAT | O_WRONLY | O_TRUNC;
	else if (node.id == ID_OUT_APPEND)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	fd = sys_error2(open(file, flag, 0644), file);
	return (fd);
}
