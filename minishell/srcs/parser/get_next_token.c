/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:57:10 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/10 09:51:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_operators(char *src, int *index);
static char	*get_word(char *src, int *index);
static int	get_quoted_word_size(char *str, char quote);

char	*get_next_token(char *src)
{
	static int	i = 0;
	char		*dest;

	dest = NULL;
	while (src[i] != '\0')
	{
		if (ft_strchr(OPERATORS, src[i]))
			dest = get_operators(src, &i);
		else if (!ft_strchr(WITHE_SPACES, src[i]))
			dest = get_word(src, &i);
		if (dest)
			return (dest);
		i++;
	}
	i = 0;
	return (0);
}

static char	*get_operators(char *src, int *index)
{
	char	*dest;
	int		src_size;

	if (!src || !index)
		return (0);
	src_size = (int)ft_strlen(src);
	if (ft_strchr("<>", src[*index]) && *index < src_size - 1)
	{
		if (src[*index] == src[*index + 1])
		{
			dest = ft_substr(src, *index, 2);
			*index += 2;
			return (dest);
		}
	}
	dest = ft_substr(src, *index, 1);
	*index += 1;
	return (dest);
}

static char	*get_word(char *src, int *index)
{
	char	*dest;
	int		i;

	i = *index;
	while (src[i])
	{
		if (ft_strchr("\"", src[i]))
			i += get_quoted_word_size(&src[i + 1], '\"');
		if (ft_strchr("\'", src[i]))
			i += get_quoted_word_size(&src[i + 1], '\'');
		if (ft_strchr(" \t\r\n\v<>|", src[i]))
			break ;
		i++;
	}
	dest = ft_substr(src, *index, i - (*index));
	*index = i;
	return (dest);
}

static int	get_quoted_word_size(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (0);
}
