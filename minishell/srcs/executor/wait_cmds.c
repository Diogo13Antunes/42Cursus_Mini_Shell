/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:33:43 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/30 17:12:32 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_last_cmd(int pid);
static void	wait_missing_cmds(int n_cmds);

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
			ft_putstr_fd("\n", STDERR_FILENO);
			set_exit_status(status + EXIT_FATAL_SIGNAL);
		}
		else
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
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
		if (WIFSIGNALED(status) && status == SIGINT)
			signal = 1;
		n_cmds--;
	}
	if (signal)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
