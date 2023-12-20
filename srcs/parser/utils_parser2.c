/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:47:25 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/31 09:28:43 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quoted_seq_size(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == s[0])
			return (i + 1);
		i++;
	}
	return (0);
}

int	get_not_quoted_seq_size(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (i);
		i++;
	}
	return (i);
}

int	get_seq_size(char *s)
{
	if (ft_strchr("\'\"", s[0]))
		return (get_quoted_seq_size(s));
	else
		return (get_not_quoted_seq_size(s));
}

int	is_word_sequence(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (i);
}
