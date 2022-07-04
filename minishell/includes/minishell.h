/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:57:16 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/04 12:54:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define PROGRAM_NAME "minish"

# define WITHE_SPACES   " \t\r\n\v"
# define OPERATORS      "<>|"

# define ID_WORD		0
# define ID_IN_REDIR	1
# define ID_OUT_REDIR	2
# define ID_IN_HERDOC	3
# define ID_OUT_APPEND	4
# define ID_PIPE		5
# define ID_CMD			6

#define BRED			"\e[1;31m"
#define BGRN			"\e[1;32m"
#define RESET			"\e[0m"

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

typedef struct s_env
{
	char			*variable;
	char			*content;
	char			*full;
	struct s_env	*next;
}				t_env;

/* get_next_token.c */
char	*get_next_token(char *src);

/* parser.c */
//t_node	*parser(char *src);
t_node	*parser(char *src, t_env *env);


/* three.c */
t_node	*create_node(int id);
void	add_new_node(t_node **tree, t_node *node);


void	print_tree(t_node *root);
void	print2D(t_node *root);


void	execution(t_node *tree, t_env *env);

void	print_node1(t_node *node);

/* utils_parser.c */
int		get_token_id(char *token);
char	*token_join_str(char *s1, char *s2);
char	*token_join_char(char *s, char c);
int		is_permited_char_env_name(char c, int i);
int		get_env_size(char *s);

/* utils_parser2.c */
int		get_quoted_seq_size(char *s);
int		get_not_quoted_seq_size(char *s);
int		get_seq_size(char *s);
int		is_word_sequence(char *s);

/* utils.c */
int		is_node_redir(t_node *node);
int		is_node_pipe(t_node *node);
int		is_node_cmd(t_node *node);
int		get_size_string_array(char **str);

/* env_vars.c */
t_env	*get_env_list(char **env);
t_env	*exist_env_elem(t_env *env, const char *elem_name);
char	**get_env_matrix(t_env *list);
t_env	*get_new_env_elem(char *env_str);
char	*create_full_env(char *var, char *cont);
int		env_lst_size(t_env *env);
int		find_char(char *str, char c);
void	ft_lstadd_back_env(t_env **lst, t_env *new);

/* get_prompt.c */
char	*get_prompt_str(t_env *env);

/* builtins/cmd_cd.c */
int		builtin_cd(char **args, t_env *env);

/* builtins/cmd_echo.c */
void	builtin_echo(char **matriz, int fd);

/* builtins/cmd_env.c */
void	builtin_env(t_env firt_elem, int fd);

/* builtins/cmd_pwd.c */
int		builtin_pwd(int fd);

/* builtins/builtin_print_export.c */
void	print_export(t_env *env, int fd);

/* builtins/builtin_check_export_elements.c */
int		check_element(char *element);
int		check_element_name(char *element);

/* builtins/cmd_export.c */
void	builtin_export(t_env *env, char **elems, int fd);

/* builtins/cmd_unset.c */
void	builtin_unset(t_env **env, char **elem);

/* error_handler.c */
void	*oom_guard(void *p);
void	cmd_not_found_error(char *cmd_path, char *cmd);
int		file_error(int err, char *file);

/* print_error.c */
void	print_msg_error(char *error, char *str);

/* pipe.c */
t_pipe	open_pipe(void);
void	close_pipe(t_pipe pipe);
void	open_pipes(t_node *tree);
void	close_pipes(t_node *tree);

/* redirections.c */
void file_redir(t_node node);
void heredoc_redir(t_node node);
void pipe_redir(t_node *node);


/* parser/words_parser.c */
char *token_parser(char *token, t_env *env);

#endif