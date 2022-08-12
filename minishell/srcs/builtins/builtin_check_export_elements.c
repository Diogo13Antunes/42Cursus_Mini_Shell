/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check_export_elements.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:19:39 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:04 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
