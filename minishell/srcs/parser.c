/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:19:12 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/21 15:41:26 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		create_ast(t_node **tree, char *token, t_env *env);
static t_node	*get_node_to_update(t_node *tree);
static t_node	*update_node(t_node *node, char *token);

char *parse_word(char *token, t_env *env);

t_node	*parser(char *src, t_env *env)
{
	char	*token;
	t_node	*tree;

	tree = NULL;
	
	token = get_next_token(src);

	while (token)
	{
		if (get_token_id(token) == ID_WORD)
			token = token_parser(token, env);
		create_ast(&tree, token, env);
		//free(token);
		token = get_next_token(src);
	}
	return (tree);
}

static void	create_ast(t_node **tree, char *token, t_env *env)
{
	int		id;
	t_node	*node;

	id = get_token_id(token);
	if (id == ID_WORD)
	{
		// update token and free. token = parse_word(token);
		//token = parse_word(token, env);
		node = get_node_to_update(*tree);
		if (node)
			update_node(node, token);
		else
			add_new_node(tree, update_node(create_node(ID_CMD), token));
	}
	else
		add_new_node(tree, create_node(id));
}

static t_node	*get_node_to_update(t_node *tree)
{
	t_node	*node;
	t_node	*next;

	if (!tree)
		return (NULL);
	if (is_node_pipe(tree))
		node = tree->rigth;
	else
		node = tree;
	if (!node)
		return (NULL);
	next = node->left;
	if ((is_node_redir(node) && !(node->data)))
		return (node);
	else if (next && is_node_redir(next) && !(next->data))
		return (next);
	else if (is_node_cmd(node))
		return (node);
	return (NULL);
}

static t_node	*update_node(t_node *node, char *token)
{
	int		size;
	t_redir	*r;
	t_cmd	*c;

	if (!node || !token)
		return (NULL);
	if (is_node_redir(node))
	{
		r = malloc(sizeof(t_redir));
		r->redir = ft_strdup(token);
		node->data = (void *) r;
	}
	else if (is_node_cmd(node))
	{
		if (!(node->data))
		{
			c = malloc(sizeof(t_cmd));
			c->cmd = NULL;
		}
		else
			c = (t_cmd *) node->data;
		c->cmd = update_string_array(c->cmd, token);
		node->data = (void *) c;
	}
	return (node);
}


//*************************************************
//	Teste de parse words: Funcional
//	Necessita refactoring e verificação de leaks
//*************************************************


char *get_env_content(t_env *env, char *var_name)
{
	t_env *elm;
	char *str;

	elm = exist_env_elem(env, var_name);
	if (!elm || !(elm->content))
		return (0);
	str = ft_substr(elm->content, 0, ft_strlen(elm->content));
	return (str);
}

static int	token_needs_parse(char *token)
{
	int sigle_quote;
	int	double_quote;
	int dollar;
	int i;

	sigle_quote = 0;
	double_quote = 0;
	dollar = 0;
	i = 0;
	while (token[i])
	{
		if (ft_strchr("\'", token[i]))
			sigle_quote++;
		else if (ft_strchr("\"", token[i]))
			double_quote++;
		else if (ft_strchr("$", token[i]))
			dollar++;
		i++;
	}
	if (sigle_quote > 1 || double_quote > 1 || dollar)
		return (1);
	return (0);
}


int is_quoted_sequence(char *s, char quote)
{
	int i;

	i = 1;
	while (s[i])
	{
		if (s[i] == quote)
			return (i + 1);
		i++;
	}
	return (0);
}

int is_word_sequence(char *s)
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

int is_word_sequence1(char *s)
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

int is_permited_env_name_char(char c, int i)
{

	if (i == 0 && (ft_isalpha(c) || c == '_'))
		return (1);
	else if (i > 0 && (ft_isalnum(c) || c == '_'))
		return (1);
	else 
		return (0);
}

int env_var_name_size(char *s)
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

char *get_str1(char *s, t_env *env)
{
	char *dst;
	char *str;
	char *new;
	int i;
	int size;

	dst = ft_calloc(1, sizeof(char));
	i = 0;
	while (s[i])
	{
		if (s[i] != '$')
		{
			size = is_word_sequence(&s[i]);
			//printf("size %i\n", size);

			str = ft_substr(&s[i], 0, size);
			new = ft_strjoin(dst, str);
			free(dst);
			dst = new;
			free(str);
			i += size - 1;
			//printf("index1 %i\n", i);
			//printf("dst |%s|\n", dst);
		}
		else if (s[i] == '$')
		{
			size = env_var_name_size(&s[i + 1]);
			//printf("size env: %i\n", size);
			if (!size)
			{
				new = ft_strjoin(dst, "$");
				free(dst);
				dst = new;	
			}
			else 
			{
				str = ft_substr(&s[i + 1], 0, size);
				//printf("env_name |%s|\n", str);
				//free(str);

				//simula que existe
				//str = ft_substr("-env_var-", 0, ft_strlen("simul_env_var"));
				str = get_env_content(env, str);
				if (str)
				{
					new = ft_strjoin(dst, str);
					free(dst);
					dst = new;
					free(str);
				}
				// Se não existir so andar para a frente
				// Não tem menos 1 porque o size não leva em conta o caracter '$'
				i += size;
			}

		}
		i++;
	}
	//printf("dst |%s|\n", dst);
	return (dst);
}

char *parse_word(char *token, t_env *env)
{
	char *dest;
	char *s;
	char *new;
	int i;
	int size;

	if (!token)
		return (0);
	if (!token_needs_parse(token))
		return (token);
	dest = NULL;
	dest = ft_calloc(1, sizeof(char));
	i = 0;
	while (token[i])
	{
		//printf("i loop %i\n", i);
		if (ft_strchr("\'", token[i]))
		{
			// verifica se é sequencia
			//printf("index antes seq verification %i\n", i);
			size = is_quoted_sequence(&token[i], '\'');
			if (size)
			{
				//printf("entra aqui\n");
				s = ft_substr(&token[i + 1], 0, size - 2);
				new = ft_strjoin(dest, s);
				free(dest);
				dest = new;
				free(s);
				i += size - 1;
				//printf("index %i\n", i);
			}
			else
			{
				new = ft_strjoin(dest, "\'");
				free(dest);
				dest = new;
			}
		}
		else if (ft_strchr("\"", token[i]))
		{
			size = is_quoted_sequence(&token[i], '\"');
			if (size)
			{
				s = get_str1(ft_substr(&token[i + 1], 0, size - 2), env);
				new = ft_strjoin(dest, s);
				free(dest);
				dest = new;
				free(s);
				i += size - 1;
			}
			else
			{
				new = ft_strjoin(dest, "\"");
				free(dest);
				dest = new;
			}
		}
		else
		{
			size = is_word_sequence1(&token[i]);
			if (size)
			{
				s = get_str1(ft_substr(&token[i], 0, size), env);
				new = ft_strjoin(dest, s);
				free(dest);
				dest = new;
				free(s);
				i += size - 1;
			}
		}
		i++;
	}
	return (dest);
}
