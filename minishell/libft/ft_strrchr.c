/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:34:09 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/03 14:52:57 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = 0;
	if (s[i] == (char)c)
		ptr = (char *) &s[i];
	while (s[i] != '\0')
	{
		i++;
		if (s[i] == (char)c)
			ptr = (char *) &s[i];
	}
	return (ptr);
}
