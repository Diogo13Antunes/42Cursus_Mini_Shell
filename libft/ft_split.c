/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:33:12 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/08 14:22:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(char const *s, char c)
{
	size_t	size;
	int		flag;

	flag = 0;
	size = 0;
	while (*s != '\0')
	{
		if (*s != c && !flag)
		{
			size++;
			flag = 1;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (size + 1);
}

char	*get_str(char const *s, char c, size_t offset)
{
	size_t	init;

	init = offset;
	while (s[offset] != c && s[offset] != '\0')
		offset++;
	return (ft_substr(s, init, (offset - init)));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	arr = malloc(get_size(s, c) * sizeof(char *));
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			arr[j] = get_str(s, c, i);
			i += ft_strlen(arr[j]) - 1;
			j++;
		}
		i++;
	}
	arr[j] = 0;
	return (arr);
}
