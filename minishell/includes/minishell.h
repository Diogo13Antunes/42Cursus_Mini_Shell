/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:57:16 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/07 19:04:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define WITHE_SPACES   " \t\r\n\v"
# define OPERATORS      "<>|"

# define ID_WORD		0
# define ID_IN_REDIR	1
# define ID_OUT_REDIR	2
# define ID_IN_HERDOC	3
# define ID_OUT_HERDOC	4
# define ID_PIPE		5
# define ID_CMD			6

typedef struct s_node
{
	int id;
	char *data;
	struct s_node *prev;
	struct s_node *left;
	struct s_node *rigth;
}   t_node;

/* get_next_token.c */
char *get_next_token(char *src);

/* parser.c */
t_node *parser(char *src);
int is_node_redir(t_node node);

/* three.c */
t_node  *create_node(int id);
void add_new_node(t_node **tree, t_node *node);

#endif