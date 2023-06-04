
#ifndef PARS_FSM_H
# define PARS_FSM_H

# include "../minishell.h"
# include <stdbool.h>

/*
	PIPE_TOK

	WORD_TOK
	QUOTE_TOK

	LESS_TOK
	GREAT_TOK
	DLESS_TOK
	DGREAT_TOK
*/

typedef enum e_parser_states
{
	VAR_STATE,
	ARGV_STATE,
	REDIR_START_STATE,
	REDIR_STATE,
}	t_parser_state;

typedef enum e_redir_type
{
	LESS_REDIR,
	GREAT_REDIR,
	DLESS_REDIR,
	DGREAT_REDIR,
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
	struct s_variable_list	*next;
}	t_var_list;

typedef char					**t_argv;

typedef struct s_cmd_list
{
	t_argv				argv;
	t_var_list			*vars;
	t_redir_list		*redirs;
	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_line
{
	t_cmd_list	*cmds;
}	t_line;

// pars_fsm.c
typedef struct s_cmd_builder	t_cb;
int				parse_tokens(t_lexer *lexer, t_cb *cb);

// pars_fsm_utils.c
bool			is_symbolic_tok(t_token_type tok_type);
bool			is_var(char *str, int *equal_pos);
t_redir_type	get_redir_type(t_token_type tok_type);
#endif
