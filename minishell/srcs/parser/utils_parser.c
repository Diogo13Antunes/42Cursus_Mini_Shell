/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:39:51 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:04 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_token_id(char *token)
{
	int	size;

	size = ft_strlen(token);
	if (size == 1)
	{
		if (token[0] == '<')
			return (ID_IN_REDIR);
		else if (token[0] == '>')
			return (ID_OUT_REDIR);
		else if (token[0] == '|')
			return (ID_PIPE);
	}
	if (size == 2)
	{
		if (token[0] == '<' && token[1] == '<')
			return (ID_IN_HERDOC);
		else if (token[0] == '>' && token[1] == '>')
			return (ID_OUT_APPEND);
	}
	return (ID_WORD);
}

char	*token_join_str(char *s1, char *s2)
{
	char	*dst;

	if (!s1 || !s2)
		return (0);
	dst = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (dst);
}

char	*token_join_char(char *s, char c)
{
	char	*dst;
	char	src[2];

	if (!s)
		return (0);
	src[0] = c;
	src[1] = '\0';
	dst = ft_strjoin(s, src);
	free(s);
	return (dst);
}

// esta  função talvés devesse fazer parte na bultin e ser usada no export
int	is_permited_char_env_name(char c, int i)
{
	if (i == 0 && (ft_isalpha(c) || c == '_'))
		return (1);
	else if (i > 0 && (ft_isalnum(c) || c == '_'))
		return (1);
	else
		return (0);
}

int	get_env_size(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_permited_char_env_name(s[i], i))
			return (i);
		i++;
	}
	return (i);
}
