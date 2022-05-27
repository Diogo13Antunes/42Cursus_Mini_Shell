/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:28:21 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/03 15:07:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	num;
	int			mult;

	i = 0;
	num = 0;
	mult = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mult = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		num = (num * 10) + str[i] - 48;
		i++;
	}
	return ((int)(num * mult));
}
