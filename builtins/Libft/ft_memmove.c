/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:10:18 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/29 11:02:12 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*a;
	char	*b;

	a = (char *) src;
	b = dest;
	if (a < b)
	{
		while (n--)
			b[n] = a[n];
	}
	else
		ft_memcpy(b, a, n);
	return (dest);
}
