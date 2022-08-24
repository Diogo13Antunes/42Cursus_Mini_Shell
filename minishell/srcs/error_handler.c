/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:16:01 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/24 10:03:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*oom_guard(void *p)
{
	if (!p)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": Out of memory!\n", STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
	return (p);
}

void	*oom_guard2(void *p)
{
	if (!p)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": Out of memory!\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (p);
}

void	directory_error(char *path, char *file)
{
	struct stat path_stat;
	int status;

	if (stat(path, &path_stat))
	{
		free(path);
		print_msg_error(strerror(errno), file);
		ft_exit(EXIT_FAILURE);
	}
	status = S_ISREG(path_stat.st_mode);
	if (!status)
	{
		free(path);
		print_msg_error("Is a directory", file);
		ft_exit(EXIT_FAILURE);
	}
}

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






int	file_error(int err, char *file)
{
	if (err == -1)
	{
		print_msg_error(strerror(errno), file);
		ft_exit(EXIT_FAILURE);
	}
	return (err);
}

int	file_error3(int err, char *file)
{
	if (err == -1)
		print_msg_error(strerror(errno), file);
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
