/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:39:39 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/30 16:18:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*home_expand2(t_env *env, char *token);

char	*home_expand(t_env *env, char *token)
{
	int		token_size;
	char	*dst;

	dst = NULL;
	if (!env || !token)
		return (NULL);
	token_size = ft_strlen(token);
	if ((token_size == 1 && token[0] == '~')
		|| (token_size >= 2 && token[0] == '~' && token[1] == '/'))
		dst = home_expand2(env, token);
	return (dst);
}

static char	*home_expand2(t_env *env, char *token)
{
	char	*dst;
	char	*token_rest;
	char	*home_path;
	t_env	*home;

	home = exist_env_elem(env, "HOME");
	if (!home || !home->content)
		return (NULL);
	dst = oom_guard(ft_calloc(1, sizeof(char)));
	home_path = ft_substr(home->content, 0, ft_strlen(home->content));
	dst = token_join_str(dst, home_path);
	token_rest = ft_substr(token, 1, ft_strlen(token));
	dst = token_join_str(dst, token_rest);
	return (dst);
}
