/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:35:30 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/30 16:49:48 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include "bonus/wildcard.h"
# include "libft/libft.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# define PURPLE "\001\x1b[35m\002"
# define RESET "\001\x1b[0m\002"
# define PROMPT "mini $ "
# define ENVAR_ARRAY_SIZE 200

int								g_exit_code;

typedef enum e_cmd_type
{
	PIPE,
	REDIRECT_OUT,
	REDIRECT_IN
}	t_cmd_type;

typedef enum e_quote_type
{
	DB_QUOTES = '\"',
	QUOTES = '\'',
	NO_QUOTES
}	t_quote_type;

typedef struct s_envar
{
	char			*name;
	char			*content;
	int				print;
	struct s_envar	*next;
}	t_envar;

typedef struct s_exec
{
	char			**argv;
	t_envar			**env;
	char			*path;
	int				in_fd;
	int				out_fd;
	t_token_type	token;
	struct s_exec	*next;
}	t_exec;

typedef struct s_command_line
{
	t_exec	*exec;
	t_envar	**environment;
	t_lexer	*lexer;
}	t_command_line;

typedef struct s_quotes
{
	t_quote_type	is_quote;
	char			*content;
	struct s_quotes	*next;
}	t_quotes;

typedef int						(*t_builtin)(t_exec *);
typedef struct s_cmd_builder	t_cb;

void			rl_clear_history(void);
void			rl_replace_line(const char *text, int clear_undo);

int				compare_quotes(char *str1, char *str2);
char			*get_prefix(char *address, int *index);
char			*get_word(char *wildcard, int *index);
int				skip_to_wildcard(int *i, int *j, char *wildcard, char *file);

char			**ft_strstrjoin(char **str1, char **str2);
char			**to_strstr(char *str);
char			*ft_strndup(char *str, size_t n);
char			**expand_wildcard(char *prefix, char *suffix);
char			*ft_strchr_no_quotes(char *str, char c);

unsigned long	get_hash_value(char *key);
void			free_envar(t_envar *var);
t_envar			*get_var(t_envar **env, char *name);
char			**get_environment(t_envar **list);
void			set_env(char **env, t_envar	**envar);
void			free_array(char **array);
int				is_var_name_valid(char *name);
int				add_var_to_envar(t_envar **env, char *str, int print);
void			add_last_exit_status(int i, t_envar **envar);
void			add_pwd_to_env(t_envar **env);
int				change_content(t_envar *node, t_envar *new_node);

int				is_var_char(char c);
void			free_quotes(t_quotes *quote);
t_quotes		*new_quote(t_quote_type type, char *content);
void			add_back(t_quotes **list, t_quotes *quote);
void			split_quotes(char *word, t_quotes **quotes);

int				add_back_inside_loop(char *word, \
t_quotes **quotes, size_t *i, size_t *j);
char			*delete_that_quote(char *quote, \
char *quote_less, int *i, int *j);
char			*get_var_content_merged(char *expanded, t_envar *var);
int				is_redir(t_token *token);
t_token			*skip_tokens(t_token *token, char c);

char			**expand_variables(char *word, t_envar **env);
char			*remove_quotes(char *quote);

long int		ms_atoi(const char *str);
int				is_builtin(char *cmd);
t_builtin		get_builtin(char *cmd);

int				run_builtin(t_exec *exec);
void			do_parent(t_exec *exec, t_exec *head);
int				wait_please(pid_t parent, t_exec *exec);

void			close_exec_fd(t_exec *exec);
void			close_all_fd(t_exec *exec);
int				free_fl(t_exec *head);
int				print_error(char *str, char *details, int exit_code);
int				is_directory(char *path);

int				ft_cd(t_exec *exec);
int				ft_echo(t_exec *exec);
int				ft_pwd(t_exec *exec);
int				ft_env(t_exec *exec);
int				ft_export(t_exec *exec);
int				ft_unset(t_exec *exec);
int				ft_exit(t_exec *exec);

void			add_to_array(t_envar **list, t_envar *node);
t_envar			*new_var(char *str, int print);
void			set_env(char **env, t_envar	**envar);

void			free_hash_list(t_envar **list);
void			free_exec(t_exec *exec);

char			*get_path(char *command, t_envar **env);
void			execute_command(t_exec *exec, t_exec *head);
int				do_exec(t_exec *exec);
char			*get_pwd(void);
void			add_empty_var(char *name, t_envar **env);

void			signal_handler_mini(void);
void			sigint_mini(int signal);
void			disable_echo(void);
void			signal_handler_fork(void);
void			sigint_fork(int signal);
void			able_echo(void);

#endif