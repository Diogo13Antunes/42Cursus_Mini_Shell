/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:39:00 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/22 10:22:13 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*defmalloc;

	defmalloc = malloc(count * size);
	if (!defmalloc)
		return (NULL);
	ft_memset(defmalloc, '\0', (count * size));
	return (defmalloc);
}
