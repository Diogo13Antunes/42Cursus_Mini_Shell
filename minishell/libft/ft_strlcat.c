/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:33:38 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/09 10:45:12 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;

	if (!dst && !src)
		return (0);
	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (size <= dst_size)
		return (src_size + size);
	i = dst_size;
	while (src[i - dst_size] != '\0' && i < size - 1)
	{
		dst[i] = src[i - dst_size];
		i++;
	}
	dst[i] = '\0';
	return (dst_size + src_size);
}
