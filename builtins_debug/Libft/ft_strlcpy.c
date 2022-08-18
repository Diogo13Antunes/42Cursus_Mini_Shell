/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:06:06 by dcandeia          #+#    #+#             */
/*   Updated: 2022/05/25 10:32:24 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (src[a] != '\0')
		a++;
	if (destsize != '\0')
	{
		while (src[b] != '\0' && b < (destsize - 1))
		{
			dest[b] = src[b];
			b++;
		}
		dest[b] = '\0';
	}
	return (a);
}

/*
#include <string.h>
#include <stdio.h>

int main()
{
	char dest[] = "";
	const char source[] = "Diogo0013";
	printf("Original \t-> %lu \n", strlcpy(dest, source, 1));
	printf("Fake \t\t-> %zu \n", ft_strlcpy(dest, source, 1));

}
*/
