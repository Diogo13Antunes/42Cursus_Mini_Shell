/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:31:32 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/27 15:13:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_signal(int signum, void (*f)())
{
    struct sigaction sa;

    sigemptyset(&(sa.sa_mask));
    sa.sa_flags = 0;
    sa.sa_handler = f;
    if (sigaction(signum, &sa, NULL) == -1)
    printf("signation error\n");
}

void hdoc_interrupt_handler(int signum)
{
    if (signum == SIGINT)
    {
		close(STDIN_FILENO);
		set_exit_status(EXIT_CTRLC_SIGNAL);
		//ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

void new_prompt_handler(int signum)
{
    if (signum == SIGINT)
    {
        rl_replace_line("", 0);
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
        rl_redisplay();
        set_exit_status(EXIT_CTRLC_SIGNAL);
    }
}