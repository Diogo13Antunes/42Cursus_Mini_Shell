/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:32:38 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/05 15:47:00 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int	i;

	if (!dst && !src)
		return (0);
	if (dst < src)
	{
		i = 0;
		while (i < (int)n)
		{
			((char *) dst)[i] = ((char *) src)[i];
			i++;
		}
	}
	else
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			((char *) dst)[i] = ((char *) src)[i];
			i--;
		}
	}
	return (dst);
}
