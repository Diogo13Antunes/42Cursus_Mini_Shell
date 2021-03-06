/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:47:19 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/24 10:47:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
	ft_strcat(msg, error);
	ft_strcat(msg, ": ");
	ft_strcat(msg, str);
	ft_strcat(msg, "\n");
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}
*/

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
	ft_strcat(msg, str);
	ft_strcat(msg, ": ");
	ft_strcat(msg, error);
	ft_strcat(msg, "\n");
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}
