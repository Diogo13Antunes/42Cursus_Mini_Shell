/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:58:50 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/01 11:35:18 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

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
