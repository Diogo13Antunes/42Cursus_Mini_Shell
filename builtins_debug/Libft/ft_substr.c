/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:51:18 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/29 11:47:51 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	a;
	size_t	i;
	char	*substring;

	if (!s)
		return (0);
	i = start;
	a = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s) + 1;
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (0);
	while (i < ft_strlen(s) && a < len)
		substring[a++] = s[i++];
	substring[a] = '\0';
	return (substring);
}

/*
#include <stdio.h>

int main()
{
	char teste[] = "www.diogo.com";
	printf("%s", ft_substr(teste, 5, 5));
}
*/