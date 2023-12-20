/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:35:05 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **matriz, int fd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (get_matrix_size(matriz) == 1)
	{
		ft_putstr_fd("\n", fd);
		return (0);
	}
	if (!ft_strncmp("-n", matriz[1], 3))
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
	if (!flag)
		ft_putstr_fd("\n", fd);
	return (0);
}
