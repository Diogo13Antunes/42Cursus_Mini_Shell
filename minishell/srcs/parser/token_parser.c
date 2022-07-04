
#include "minishell.h"

static char *update_token(char *dst, char *token, int *index, t_env *env);
static char *update_token_with_env_vars(char *s, t_env *env);
static char *add_env_var_to_token(t_env *env, char *s, char *dst, int *i);
static int	token_needs_parse(char *token);
static int get_quoted_seq_size(char *s);
static int get_not_quoted_seq_size(char *s);
static int get_seq_size(char *s);
static int is_word_sequence(char *s);
static int get_env_var_size(char *s);
static int is_permited_env_name_char(char c, int i);
static char *token_join_str(char *s1, char *s2);
static char *token_join_char(char *s1, char c);


/*
	teste strimg: tes"te"-aa$bb"'cc$dd''
*/

char *token_parser(char *token, t_env *env)
{
	char *dst;
	char *s;
	int i;
	int size;

	if (!token)
		return (0);
	if (!token_needs_parse(token))
		return (token);
	i = 0;
	dst = ft_calloc(1, sizeof(char));
	while (token[i])
	{
		dst = update_token(dst, token, &i, env);
		i++;
	}	
	free(token);
	return (dst);
}

static char *update_token(char *dst, char *token, int *index, t_env *env)
{
	char *str;
	int size;
	int i;

	i = *index;
	size = get_seq_size(&token[i]);
	if (size)
	{
		if (ft_strchr("\'\"", token[i]))
		{
			str = ft_substr(&token[i + 1], 0, size - 2);
			if (token[i] == '\"')
				str = update_token_with_env_vars(str, env);
		}
		else 
			str = update_token_with_env_vars(ft_substr(&token[i], 0, size), env);
		dst = token_join_str(dst, str);
		*index += size - 1;
	}
	else 
		dst = token_join_char(dst, token[i]);
	return (dst);
}

static char *update_token_with_env_vars(char *s, t_env *env)
{
	char *dst;
	char *str;
	int i;
	int size;

	dst = ft_calloc(1, sizeof(char));
	i = 0;
	while (s[i])
	{
		if (s[i] != '$')
		{
			size = is_word_sequence(&s[i]);
			dst = token_join_str(dst, ft_substr(&s[i], 0, size));
			i += size - 1;
		}
		else if (s[i] == '$')
			dst = add_env_var_to_token(env, s, dst, &i);
		i++;
	}
	return (dst);
}

static char *add_env_var_to_token(t_env *env, char *s, char *dst, int *i)
{
	t_env *elm;
	char *str;
	char *env_name;
	int size;


	size = get_env_var_size(&s[*i + 1]);
	if (!size)
		return (token_join_char(dst, s[*i]));
	else 
	{
		env_name = ft_substr(&s[*i + 1], 0, size);
		elm = exist_env_elem(env, env_name);
		if (elm && elm->content)
			dst = token_join_str(dst, elm->content);
		free(env_name);
		*i += size;
	}
	return (dst);
}

static int	token_needs_parse(char *token)
{
	int s_quote;
	int	d_quote;
	int dollar;
	int i;

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

static int get_quoted_seq_size(char *s)
{
	int i;

	i = 1;
	while (s[i])
	{
		if (s[i] == s[0])
			return (i + 1);
		i++;
	}
	return (0);
}

static int get_not_quoted_seq_size(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (i);
		i++;
	}
	return (i);
}

static int get_seq_size(char *s)
{
	if (ft_strchr("\'\"", s[0]))
		return (get_quoted_seq_size(s));
	else 
		return (get_not_quoted_seq_size(s));
}

static int is_word_sequence(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

static int get_env_var_size(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!is_permited_env_name_char(s[i], i))
			return (i);
		i++;
	}
	return (i);
}


static int is_permited_env_name_char(char c, int i)
{

	if (i == 0 && (ft_isalpha(c) || c == '_'))
		return (1);
	else if (i > 0 && (ft_isalnum(c) || c == '_'))
		return (1);
	else 
		return (0);
}


static char *token_join_str(char *s1, char *s2)
{
	char *dst;

	if (!s1 || !s2)
		return (0);
	dst = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (dst);
}

static char *token_join_char(char *s1, char c)
{
	char *dst;
	char src[2];

	if (!s1)
		return (0);
	src[0] = c;
	src[1] = '\0';
	dst = ft_strjoin(s1, src);
	free(s1);
	return (dst);
}