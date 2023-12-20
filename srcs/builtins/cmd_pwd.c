/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:02:20 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/30 17:09:03 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int fd)
{
	char	*address;

	address = getcwd(NULL, 0);
	if (!address)
		return (-1);
	ft_putstr_fd(address, fd);
	ft_putstr_fd("\n", fd);
	free_str(address);
	return (0);
}
