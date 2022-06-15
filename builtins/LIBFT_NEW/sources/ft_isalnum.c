/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:07:59 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/19 12:17:41 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int main()
{
	int letra = 'A', numero = '7', caracter = '%';
	printf("Letra \t\t-> %d \n", ft_isalnum(letra));
	printf("Numero \t\t-> %d \n", ft_isalnum(numero));
	printf("Caracter \t-> %d \n", ft_isalnum(caracter));
}
*/
