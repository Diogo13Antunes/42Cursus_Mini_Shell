/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:04:05 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/25 15:10:47 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s, const char *set)
{
	size_t	i;

	if (!s || !set)
		return (0);
	while (*s && ft_strchr(set, *s))
		s++;
	i = ft_strlen(s);
	while (i && ft_strchr(set, s[i]))
		i--;
	return (ft_substr(s, 0, i + 1));
}
