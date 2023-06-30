/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:45:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 14:57:05 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
# include <stdbool.h>

typedef enum e_check_quotes
{
	START,
	SINGLE_OPEN,
	SINGLE_CLOSE,
	DOUBLE_OPEN,
	DOUBLE_CLOSE,
}	t_check_quotes;

typedef enum e_parser_states
{
	VAR_STATE,
	ARGV_STATE,
	REDIR_START_STATE,
	REDIR_STATE,
}	t_parser_state;

typedef enum e_redir_type
{
	IN_REDIR,
	OUT_REDIR,
	HEREDOC_REDIR,
	APPEND_REDIR,
}	t_redir_type;

typedef struct s_redir_list
{
	enum e_redir_type	redir_type;
	char				*word;
	struct s_redir_list	*next;
}	t_redir_list;

typedef struct s_variable_list
{
	char					*name;
	char					*value;
	int						flag;
	struct s_variable_list	*next;
}	t_var_list;

typedef char					**t_argv;

typedef struct s_cmd_list
{
	t_argv				argv;
	t_var_list			*vars;
	t_redir_list		*redirs;
	int					flag_is_export;
	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_line
{
	t_cmd_list	*cmds;
}	t_line;

typedef struct s_cmd_builder	t_cb;
typedef struct s_envar			t_envar;

typedef struct s_pars
{
	t_token			*token;
	t_parser_state	state;
	t_redir_type	redir_type;
}	t_pars;

//				parser.c
int				parse_tokens(t_lexer *lexer, t_cb *cb, t_envar **env);
int				init_t_pars(t_pars *pars, t_lexer *lexer, t_cb **cb);
int				if_var_state(t_pars *pars, t_cb **cb, t_envar **env);
int				give_var_to_cb(t_pars *pars, t_cb **cb, t_envar **env);

//				parser_utils.c
int				malloc2(size_t count, void **ptr);
int				print_malloc_failed(void);
bool			is_var(char *str, int *equal_pos);
t_redir_type	get_redir_type(t_token_type tok_type);
bool			is_quotes_close(char *str);

//				pars_states.c
int				if_argv_state(t_pars *pars, t_cb **cb, t_envar **env);
int				if_pipe(t_pars *pars, t_cb **cb);
void			give_argv_to_cb(t_cb **cb, t_token *token, t_envar **env);
int				if_redir_state(t_pars *pars, t_cb **cb, t_envar **env);
void			give_redir_to_cb(t_cb **cb, t_token *token,
					t_envar **env, t_redir_type redir_type);

#endif
