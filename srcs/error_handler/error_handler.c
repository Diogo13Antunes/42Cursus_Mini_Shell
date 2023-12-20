/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:16:01 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/31 10:06:02 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found_error(char *cmd_path, char *cmd)
{
	if (!cmd_path || !cmd)
	{
		print_msg_error("command not found", cmd);
		ft_exit(EXIT_CMD_NFOUND);
	}
}

int	cmd_path_error(int err, char *msg, char *file)
{
	if (err == -1)
	{
		print_msg_error(msg, file);
		ft_exit(EXIT_CMD_NEXEC);
	}
	return (err);
}

int	sys_error(int err, char *resource)
{
	if (err == -1)
	{
		print_msg_error(strerror(errno), resource);
		ft_exit(EXIT_FAILURE);
	}
	return (err);
}

int	sys_error2(int err, char *resource)
{
	if (err == -1)
		print_msg_error(strerror(errno), resource);
	return (err);
}
