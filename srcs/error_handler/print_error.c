/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:47:19 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/29 16:20:02 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_msg_error(char *error, char *str)
{
	int		msg_size;
	char	*msg;

	msg_size = 6;
	msg_size += ft_strlen(PROGRAM_NAME);
	msg_size += ft_strlen(error);
	msg_size += ft_strlen(str);
	msg = oom_guard(ft_calloc(msg_size, sizeof(char)));
	ft_strcat(msg, PROGRAM_NAME);
	ft_strcat(msg, ": ");
	if (str)
	{
		ft_strcat(msg, str);
		ft_strcat(msg, ": ");
	}
	ft_strcat(msg, error);
	ft_strcat(msg, "\n");
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

void	print_msg_error2(char *err1, char *err2, char *str)
{
	int		msg_size;
	char	*msg;

	msg_size = 10;
	msg_size += ft_strlen(PROGRAM_NAME);
	msg_size += ft_strlen(err1);
	msg_size += ft_strlen(err2);
	msg_size += ft_strlen(str);
	msg = oom_guard(ft_calloc(msg_size, sizeof(char)));
	ft_strcat(msg, PROGRAM_NAME);
	ft_strcat(msg, ": ");
	if (str)
	{
		ft_strcat(msg, str);
		ft_strcat(msg, ": ");
	}
	ft_strcat(msg, err1);
	ft_strcat(msg, ": ");
	ft_strcat(msg, err2);
	ft_strcat(msg, "\n");
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}
