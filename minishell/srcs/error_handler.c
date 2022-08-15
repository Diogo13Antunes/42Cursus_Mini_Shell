/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:16:01 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
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

/*
void	cmd_not_found_error(char *cmd_path, char *cmd)
{
	if (!cmd_path)
	{
		print_msg_error("command not found", cmd);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
}

void	cmd_not_found_error2(int err, char *cmd, char *str)
{
	if (err == -1)
	{
		if (str)
			free(str);
		print_msg_error("command not found", cmd);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	//return (err);
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

int	file_error3(int err, char *file, char *str)
{

	if (err)
	{
		if (str)
			free(str);
		print_msg_error(strerror(errno), file);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

void	directory_error(char *path, char *file)
{
	struct stat path_stat;
	int status;

	if (stat(path, &path_stat))
	{
		free(path);
		print_msg_error(strerror(errno), file);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	status = S_ISREG(path_stat.st_mode);
	if (!status)
	{
		free(path);
		print_msg_error("Is a directory", file);
		exit(EXIT_FAILURE);
	}
}
*/

void	directory_error(char *path, char *file)
{
	struct stat path_stat;
	int status;

	if (stat(path, &path_stat))
	{
		free(path);
		print_msg_error(strerror(errno), file);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	status = S_ISREG(path_stat.st_mode);
	if (!status)
	{
		free(path);
		print_msg_error("Is a directory", file);
		exit(EXIT_FAILURE);
	}
}

int	sys_error(int err, char *file)
{
	if (err)
	{
		print_msg_error(strerror(errno), file);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
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

int	sys_error2(int err, char *msg, char *file)
{
	if (err == -1)
	{
		print_msg_error(msg, file);
		//free_alloc_mem();
		exit(EXIT_FAILURE);
	}
	return (err);
}

int	file_error3(int err, char *file)
{
	if (err == -1)
	{
		print_msg_error(strerror(errno), file);
		//free_alloc_mem();
		//exit(EXIT_FAILURE);
	}
	return (err);
}

void	cmd_not_found_error(char *cmd_path, char *cmd)
{
	if (!cmd_path || !cmd)
	{
		print_msg_error("command not found", cmd);
		//free_alloc_mem();
		exit(EXIT_CMD_NFOUND);
	}
}

int	cmd_path_error(int err, char *msg, char *file)
{
	if (err == -1)
	{
		print_msg_error(msg, file);
		//free_alloc_mem();
		exit(EXIT_CMD_NEXEC);
	}
	return (err);
}