/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:23:32 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/30 13:02:44 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*update_token(char *dst, char *token, int *index, t_env *env);
static char	*update_token_env_var(char *s, t_env *env);
static char	*add_env_var_to_token(t_env *env, char *s, char *dst, int *i);
static int	token_needs_parse(char *token);

char	*token_parser(char *token, t_env *env, int exit_code)
{
	char	*dst;
	char	*s;
	int		i;

	if (!token)
		return (0);
	if (!token_needs_parse(token))
		return (token);
	ft_exit_code(exit_code);
	i = 0;
	dst = oom_guard(ft_calloc(1, sizeof(char)));
	while (token[i])
	{
		dst = update_token(dst, token, &i, env);
		i++;
	}	
	free(token);
	return (dst);
}

static char	*update_token(char *dst, char *token, int *index, t_env *env)
{
	char	*str;
	int		size;
	int		i;

	i = *index;
	size = get_seq_size(&token[i]);
	if (size)
	{
		if (ft_strchr("\'\"", token[i]))
		{
			str = oom_guard(ft_substr(&token[i + 1], 0, size - 2));
			if (token[i] == '\"')
				str = update_token_env_var(str, env);
		}
		else
			str = update_token_env_var(ft_substr(&token[i], 0, size), env);
		dst = token_join_str(dst, str);
		*index += size - 1;
	}
	else
		dst = token_join_char(dst, token[i]);
	return (dst);
}

static char	*update_token_env_var(char *s, t_env *env)
{
	char	*dst;
	int		size;
	int		i;

	dst = oom_guard(ft_calloc(1, sizeof(char)));
	i = 0;
	while (s[i])
	{
		if (s[i] != '$')
		{
			size = is_word_sequence(&s[i]);
			dst = token_join_str(dst, ft_substr(&s[i], 0, size));
			i += size - 1;
		}
		else if (s[i] == '$' && s[i + 1] == '?')
		{
			dst = token_join_str(dst, ft_itoa(ft_exit_code(-1)));
			i += 1;
		}
		else if (s[i] == '$')
			dst = add_env_var_to_token(env, s, dst, &i);
		i++;
	}
	return (dst);
}

static char	*add_env_var_to_token(t_env *env, char *s, char *dst, int *i)
{
	t_env	*elm;
	char	*env_name;
	int		size;

	size = get_env_size(&s[*i + 1]);
	if (!size)
		dst = token_join_char(dst, s[*i]);
	else
	{
		env_name = ft_substr(&s[*i + 1], 0, size);
		elm = exist_env_elem(env, env_name);
		if (elm && elm->content)
			dst = token_join_str(dst, ft_strdup(elm->content));
		free_str(env_name);
		*i += size;
	}
	return (dst);
}

static int	token_needs_parse(char *token)
{
	int	s_quote;
	int	d_quote;
	int	dollar;
	int	i;

	s_quote = 0;
	d_quote = 0;
	dollar = 0;
	i = 0;
	while (token[i])
	{
		if (ft_strchr("\'", token[i]))
			s_quote++;
		else if (ft_strchr("\"", token[i]))
			d_quote++;
		else if (ft_strchr("$", token[i]))
			dollar++;
		i++;
	}
	if (s_quote > 1 || d_quote > 1 || dollar)
		return (1);
	return (0);
}
