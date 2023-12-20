/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:34:18 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/04 19:19:32 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_size;

	if (!s)
		return (0);
	s_size = ft_strlen(s);
	if (start >= s_size)
		len = 0;
	else if (len > s_size - start)
		len = s_size - start;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
