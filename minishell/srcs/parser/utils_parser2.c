/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:47:25 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/16 11:27:39 by dsilveri         ###   ########.fr       */
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

int	ft_exit_code(int status)
{
	static int	st = 0;

	if (status >= 0)
		st = status;
	return (st);
}
