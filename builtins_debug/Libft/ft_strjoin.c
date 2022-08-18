/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:11:21 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/29 11:37:34 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	a;
	size_t	len;
	char	*dst;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (0);
	a = 0;
	while (s1[a])
		dst[i++] = s1[a++];
	a = 0;
	while (s2[a])
		dst[i++] = s2[a++];
	dst[i] = '\0';
	return (dst);
}
