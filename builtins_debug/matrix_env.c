/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:35:44 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/06 12:23:53 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

char	**get_env_matrix(t_env *list)
{
	int		lst_size;
	char	**matrix;
	t_env	*temp;
	int		i;

	i = 0;
	temp = list;
	lst_size = ft_lstsize(list);
	matrix = ft_calloc(sizeof(char *), lst_size + 1);
	while (temp)
	{
		matrix[i] = temp->full;
		i++;
		temp = temp->next;
	}
	return (matrix);
}
