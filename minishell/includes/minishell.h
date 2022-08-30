/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:57:16 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/30 16:37:36 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdbool.h>

# include "../libft/libft.h"

# define PROGRAM_NAME "minish"

# define WHITE_SPACES   " \t\r\n\v\f"
# define OPERATORS      "<>|"

# define ID_WORD		0
# define ID_IN_REDIR	1
# define ID_OUT_REDIR	2
# define ID_IN_HERDOC	3
# define ID_OUT_APPEND	4
# define ID_PIPE		5
# define ID_CMD			6

# define BRED			"\e[1;31m"
# define BGRN			"\e[1;32m"
# define RESET			"\e[0m"

# define EXIT_BUILTIN		1
# define EXIT_SYNTAX 		2
# define EXIT_CMD_NFOUND 	127
# define EXIT_CMD_NEXEC		126
# define EXIT_FATAL_SIGNAL 	128
# define EXIT_CTRLC_SIGNAL 	130

# define HDOC_SUCCESS		0
# define HDOC_STOP_CTRL_C	1
# define HDOC_STOP_CTRL_D	2

# define NO_TYPE     0
# define TYPE_TREE   1
# define TYPE_ENV    2

typedef struct s_node
{
	int				id;
	void			*data;
	struct s_node	*prev;
	struct s_node	*left;
	struct s_node	*rigth;
}				t_node;

typedef struct s_redir
{
	char	*redir;
}	t_redir;

typedef struct s_cmd
{
	char	**cmd;
}	t_cmd;

typedef struct s_pipe
{
	int		r;
	int		w;
}	t_pipe;

typedef struct s_hdoc
{
	t_pipe	p;
	char	*end;
}	t_hdoc;

typedef struct s_exit_status
{
	int	code;
	int	signal;
}	t_exit_status;

typedef struct s_env
{
	char			*variable;
	char			*content;
	char			*full;
	struct s_env	*next;
}				t_env;

typedef struct s_alloc_mem
{
	t_env	*env;
	t_node	*tree;
}	t_alloc_mem;

/* builtins/builtin_check_export_elements.c */
int		check_element(char *element);

/* builtins/builtin_print_export.c */
void	print_export(t_env *env, int fd);

/* builtins/cmd_cd.c */
int		builtin_cd(char **args, t_env *env);

/* builtins/cmd_echo.c */
int		builtin_echo(char **matriz, int fd);

/* builtins/cmd_env.c */
int		builtin_env(t_env firt_elem, int fd);

/* builtins/cmd_exit.c */
void	builtin_exit(void);

/* builtins/cmd_export.c */
int		builtin_export(t_env *env, char **elems, int fd);

/* builtins/cmd_pwd.c */
int		builtin_pwd(int fd);

/* builtins/cmd_unset.c */
int		builtin_unset(t_env **env, char **elem);

/* env_vars/env_lst.c */
t_env	*get_new_env_elem(char *env_str);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*get_env_list(char **env);

/* env_vars/env_vars.c */
int		env_lst_size(t_env *env);
char	**get_env_matrix(t_env *list);
char	*create_full_env(char *var, char *cont);
t_env	*exist_env_elem(t_env *env, const char *elem_name);

/* env_vars/free_env_lst.c */
void	free_env_lst(t_env	*env);

/* error_handler/error_handler.c */
void	cmd_not_found_error(char *cmd_path, char *cmd);
int		cmd_path_error(int err, char *msg, char *file);
int		sys_error(int err, char *resource);
int		sys_error2(int err, char *resource);

/* error_handler/error_handler2.c */
void	*oom_guard(void *p);
void	*oom_guard2(void *p);

/* error_handler/print_error.c */
void	print_msg_error(char *error, char *str);
void	print_msg_error2(char *err1, char *err2, char *str);

/* executor/exec_builtins.c*/
int		is_builtin(char *cmd);
int		is_builtin_without_pipe(t_node *tree);
void	exec_builtin(char **cmd, t_env *env, int fd);
void	run_builtin_branch(t_node *tree, t_env *env);

/* executor/executor.c*/
void	execution(t_node *tree, t_env *env);

/* executor/file_redir.c*/
void	file_redir(t_node node);
int		get_file_fd(t_node node);

/* executor/get_cmd_path.c*/
char	*get_cmd_path(char *cmd, t_env *env);

/* executor/hdoc.c */
int		hdoc_exec(t_node *tree);
void	close_hdoc(t_node *tree);
void	hdoc_redir(t_node *node);

/* executor/pipe.c */
t_pipe	open_pipe(void);
void	close_pipe(t_pipe pipe);
void	open_pipes(t_node *tree);
void	close_pipes(t_node *tree);
void	pipe_redir(t_node *node);

/* executor/utils_executor.c */
void	close_fd(int fd);
int		get_num_cmds(t_node *tree);
int		convert_hdoc_stop_code(int code);

/* executor/wait_cmds.c */
void	wait_cmds(int last_pid, int n_cmds);

/* parser/get_next_token.c */
char	*get_next_token(char *src, int reset);

/* parser/parser.c */
t_node	*parser(char *src, t_env *env);

/* parser/syntax_error.c */
int		is_syntax_error(t_node *tree, char *token);

/* parser/token_parser.c */
char	*token_parser(char *token, t_env *env, int exit_code);

/* parser/update_node.c */
t_node	*update_node(t_node *node, char *token);

/* parser/utils_parser.c */
int		get_token_id(char *token);
char	*token_join_str(char *s1, char *s2);
char	*token_join_char(char *s, char c);
int		is_permited_char_env_name(char c, int i);
int		get_env_size(char *s);

/* parser/utils_parser2.c */
int		get_quoted_seq_size(char *s);
int		get_not_quoted_seq_size(char *s);
int		get_seq_size(char *s);
int		is_word_sequence(char *s);
int		ft_exit_code(int status);

/* parser/home_expand.c */
char	*home_expand(t_env *env, char *token);

/* tree/add_new_node.c */
void	add_new_node(t_node **tree, t_node *node);

/* tree/free_tree.c*/
void	free_tree(t_node *tree);

/* tree/three.c */
t_node	*create_node(int id);
void	add_node_after_on_left(t_node *node, t_node *new_node);
void	add_node_after_on_right(t_node *node, t_node *new_node);
void	add_node_on_top(t_node **tree, t_node *node);

/* alloc_mem.c */
void	init_alloc_mem(void);
void	save_alloc_mem(void *mem, int type);
void	free_all_alloc_mem(void);

/* exit_status.c */
void	set_exit_status(int exit_status);
int		get_exit_status(void);
void	clear_exit_status(void);

/* get_prompt.c */
char	*get_prompt_str(t_env *env);

/* signal_handler.c */
void	set_signal(int signum, void (*f)());
void	hdoc_interrupt_handler(int signum);
void	new_prompt_handler(int signum);

/* utils.c */
int		is_node_redir(t_node *node);
int		is_node_pipe(t_node *node);
int		is_node_cmd(t_node *node);
int		is_node_hdoc(t_node *node);
int		get_matrix_size(char **str);

/* utils2.c */
void	free_matrix(char **m);
void	free_str(char *str);
void	ft_exit(int status);
int		get_char_index(char *str, char c);

#endif