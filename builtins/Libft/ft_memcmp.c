/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 08:46:50 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/25 14:11:20 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/*
#include <string.h>
#include <stdio.h>

int main()
{
    char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};
    printf("Original: \t%d \n", memcmp(s2, s3, 4));
    printf("Fake: \t\t%d \n", ft_memcmp(s2, s3, 4));
}
*/