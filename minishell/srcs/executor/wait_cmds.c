/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:33:43 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/22 14:04:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_missing_cmds(int n_cmds);
static void	wait_last_cmd(int pid);

void	wait_cmds(int last_pid, int n_cmds)
{
	wait_last_cmd(last_pid);
	wait_missing_cmds(n_cmds);
}

static void	wait_last_cmd(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (status < 130)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			set_exit_status(status + EXIT_FATAL_SIGNAL);
		}
		else
		{
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
			set_exit_status(status);
		}
	}		
}

static void	wait_missing_cmds(int n_cmds)
{
	int	status;
	int	signal;

	signal = 0;
	n_cmds--;
	while (n_cmds)
	{
		wait(&status);
		if (WIFSIGNALED(status) && status < 130)
			signal = 1;
		n_cmds--;
	}
	if (signal)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
