/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:10:40 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/01 14:40:00 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	builtin_echo(char **matriz, int fd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_strncmp("-n", matriz[1], 3) == 0)
	{
		i++;
		flag = 1;
	}
	while (matriz[i])
	{
		ft_putstr_fd(matriz[i], fd);
		if (matriz[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag != 1)
		ft_putstr_fd("\n", fd);
	return ;
}
