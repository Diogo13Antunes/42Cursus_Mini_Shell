/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:01:05 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/21 18:38:57 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
	{
		c += 32;
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