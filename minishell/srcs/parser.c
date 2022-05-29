/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:57:10 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/29 18:40:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *get_redir(char *src, int *index);
static char *get_word(char *src, int *index);

char *get_next_token(char *src)
{
	static int	i = 0;
	char		*dest;
	
	while (src[i] != '\0')
	{
		if (src[i] == '<' || src[i] == '>')
		{
			dest = get_redir(src, &i);
			return (dest);
		}
		else if (!ft_strchr(WITHE_SPACES, src[i]))
		{
			dest = get_word(src, &i);
			return (dest);
		}
		i++;
	}
	i = 0;
	return (0);
}

static char *get_redir(char *src, int *index)
{
	char	*dest;

	if (*index < (int)ft_strlen(src) - 1)
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


static char *get_word(char *src, int *index)
{
	char	*dest;
	int		i;

	i = *index;
	while(src[i])
	{
		if (ft_strchr(" \t\r\n\v<>()|", src[i]))
			break;
		i++;
	}
	dest = ft_substr(src, *index, i - (*index));
	*index = i;
	return (dest);
}
