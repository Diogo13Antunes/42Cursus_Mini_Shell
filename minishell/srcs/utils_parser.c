/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:39:51 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/21 12:42:10 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (ID_OUT_HERDOC);
	}
	return (ID_WORD);
}

int	get_size_string_array(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**update_string_array(char **str, char *token)
{
	char	**new_arr;
	char	**buff;
	int		arr_size;
	int		i;

	if (!str)
	{
		new_arr = malloc(2 * sizeof(char *));
		new_arr[0] = ft_strdup(token);
		new_arr[1] = NULL;
	}
	else
	{
		arr_size = get_size_string_array(str);
		new_arr = malloc((arr_size + 2) * sizeof(char *));
		i = -1;
		while (str[++i])
			new_arr[i] = str[i];
		new_arr[i] = ft_strdup(token);
		new_arr[i + 1] = 0;
		free(str);
	}
	return (new_arr);
}
