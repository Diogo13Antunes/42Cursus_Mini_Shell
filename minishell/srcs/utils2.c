/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:59:11 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/23 16:16:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **m)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (m[i])
	{
		free_str(m[i]);
		i++;
	}
	free(m);
}

void	free_str(char *str)
{
	if (str)
		free(str);
}

void ft_exit(int status)
{
	free_all_alloc_mem();
	exit(status);
}

