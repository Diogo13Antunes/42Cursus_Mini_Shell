/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:33:15 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/22 10:48:28 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = (char *)malloc((sizeof(char)) * (ft_strlen(s1) + 1));
	if (dst == NULL)
		return (0);
	ft_memcpy(dst, s1, ft_strlen(s1) + 1);
	return (dst);
}
/*
int	main(void)
{
	char *test;
	char *dup;

	test = "Testando a função strdup!";
	printf("test = %s\n", test);
	dup = ft_strdup(test);
	printf("dup  = %s\n", dup);
	free(dup);
}
*/