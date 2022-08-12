/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 11:51:29 by diogoantune       #+#    #+#             */
/*   Updated: 2022/08/12 12:05:53 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	*reset_sig(void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((char *)s)[i] = (unsigned char)c;
	return (s);
}

static void	signals_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		// rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	signals_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "> \n", 3);
	}
}

static void	signal_choice(struct sigaction *sig, int signal)
{
	reset_sig(sig, '\0', sizeof(sig));
	sig->sa_flags = SA_SIGINFO;
	sigemptyset(&sig->sa_mask);
	if (signal == SG_IGN)
		(sig->__sigaction_u.__sa_handler) = SIG_IGN;
	else if (signal == SG_HD)
		(sig->__sigaction_u.__sa_handler) = signals_handler;
	else if (signal == SG_RDL)
		(sig->__sigaction_u.__sa_handler) = signals_heredoc;
	else if (signal == SG_DFL)
		(sig->__sigaction_u.__sa_handler) = SIG_DFL;
	else
		return ;
}

int	signals_call(int choice)
{
	struct sigaction	sig;

	signal_choice(&sig, choice);
	if (sigaction(SIGQUIT, &sig, NULL) == -1
		|| sigaction(SIGINT, &sig, NULL) == -1)
	{
		printf("Error: Handling Signals!\n");
		exit(1);
	}
}
