/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:02:20 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int fd)
{
	char	*address;
	int		i;

	i = 0;
	address = getcwd(NULL, 0);
	if (!address)
		return (-1);
	ft_putstr_fd(address, fd);
	ft_putstr_fd("\n", fd);
	free(address);
	return (0);
}
