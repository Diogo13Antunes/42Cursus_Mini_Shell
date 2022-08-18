/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:37:07 by dcandeia          #+#    #+#             */
/*   Updated: 2022/05/31 13:59:16 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strlcat(char *dst, const char *src, int dstsize)
{
	int	c;
	int	d;

	if (!dst || !src)
		return (0);
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	c = ft_strlen(dst);
	d = 0;
	while (src[d] != '\0' && c + 1 < dstsize)
	{
		dst[c] = src[d];
		c++;
		d++;
	}
	dst[c] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}

/*
#include <string.h>
#include <stdio.h>

int main()
{
	char dest[] = "BBBB0000000000000000000000000";
	char source[] = "AAAAAAAAA";
	printf("Original \t-> %lu \n", strlcat(dest, source, 6));
	printf("Fake \t\t-> %zu \n", ft_strlcat(dest, source, 6));	
}
*/