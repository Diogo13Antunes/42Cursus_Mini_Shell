/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:57:16 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/20 14:44:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
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
	void *data;
	struct s_node *prev;
	struct s_node *left;
	struct s_node *rigth;
}   t_node;

typedef struct s_redir
{
	char *redir;
}	t_redir;

typedef struct s_cmd
{
	char **cmd;
}	t_cmd;

typedef struct s_pipe
{
	int r;
	int w;
}	t_pipe;

/* get_next_token.c */
char *get_next_token(char *src);

/* parser.c */
t_node *parser(char *src);
int	is_node_redir(t_node *node);
int	is_node_pipe(t_node *node);
int	is_node_cmd(t_node *node);

/* three.c */
t_node  *create_node(int id);
void add_new_node(t_node **tree, t_node *node);


void print_tree(t_node *root);
void print2D(t_node *root);


void execution(t_node *tree, char **env);
void open_pipes(t_node *tree);
int get_num_of_pipes(t_node *tree);


void print_node1(t_node *node);

#endif