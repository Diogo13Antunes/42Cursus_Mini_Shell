/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check_export_elements.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:19:39 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/23 14:50:18 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_element_name(char *element)
{
	char	c;

	c = element[0];
	if (!(ft_isalpha(c) || c == '_'))
		return (0);
	c = element[1];
	while (c)
	{
		if (c == '=')
			break ;
		if (!(ft_isalnum(c) || c == '_'))
			return (0);
		c = *(++element);
	}
	return (1);
}

int	check_element(char *element)
{
	if (check_element_name(element))
		return (1);
	return (0);
}
