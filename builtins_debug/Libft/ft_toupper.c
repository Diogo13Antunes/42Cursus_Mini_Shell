/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:18:57 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/20 12:57:17 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
	{
		c -= 32;
		return (c);
	}
	else
		return (c);
}
/*
#include <stdio.h>

int main()
{
	char a, b, c;
	a = 'a';
	b = 'B';
	c = '7';
	printf("%c \n", ft_toupper(a));
	printf("%c \n", ft_toupper(b));
	printf("%c \n", ft_toupper(c));
}
*/