/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:30:01 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/05 11:46:00 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(long int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}	
	return (i);
}

char	*ft_itoa(int n)
{
	int			size;
	char		*str;
	long int	nbr;

	nbr = (long int) n;
	size = get_size(nbr);
	str = malloc((1 + size) * sizeof(char));
	if (!str)
		return (0);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	else if (nbr == 0)
		str[0] = '0';
	str[size] = '\0';
	while (nbr > 0)
	{
		str[--size] = (nbr - ((nbr / 10) * 10)) + '0';
		nbr /= 10;
	}
	return (str);
}
