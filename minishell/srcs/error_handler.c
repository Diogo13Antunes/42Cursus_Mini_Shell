/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:16:01 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/24 10:25:26 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*oom_guard(void *p)
{
	if (!p)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": Out of memory!\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (p);
}

void	cmd_not_found_error(char *cmd_path, char *cmd)
{
	if (!cmd_path)
	{
		print_msg_error("command not found", cmd);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
}

int	file_error(int err, char *file)
{
	if (err == -1)
	{
		print_msg_error(strerror(errno), file);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

int	file_error2(int err, char *file)
{
	if (err == -1)
	{
		print_msg_error(strerror(errno), file);
		//free_alloc_mem();
		//exit(EXIT_FAILURE);
	}
	return (err);
}

