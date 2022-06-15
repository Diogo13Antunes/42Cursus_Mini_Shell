/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:34:34 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/26 15:48:10 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size_0(int n)
{
	int	size;

	size = 0;
	if (n > 0)
		size = 0;
	else
		size = 1;
	return (size);
}

int	ft_sinal(int n)
{
	int	sinal;

	sinal = 0;
	if (n < 0)
		sinal = -1;
	else
		sinal = 1;
	return (sinal);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	size = ft_size_0(n);
	nbr = (long)n * ft_sinal(n);
	while (n)
	{
		n /= 10;
		size++;
	}
	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	*(str + size--) = '\0';
	while (nbr > 0)
	{
		*(str + size--) = nbr % 10 + '0';
		nbr /= 10;
	}
	if (size == 0 && str[1] == '\0')
		*(str + size) = '0';
	else if (size == 0 && str[1] != '\0')
		*(str + size) = '-';
	return (str);
}
/*
#include <stdio.h>

int main()
{
	printf("Numero  13 -> \t%s \n", ft_itoa(13));
	printf("Numero -13 -> \t%s \n", ft_itoa(-13));
}
*/