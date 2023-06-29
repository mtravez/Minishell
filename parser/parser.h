
#ifndef PARSER
# define PARSER

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
	IN_REDIR, // <
	OUT_REDIR, // >
	HEREDOC_REDIR, // <<
	APPEND_REDIR, // >>
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

//				pars_fsm.c
int				parse_tokens(t_lexer *lexer, t_cb *cb, t_envar **env);
int				print_syn_error(t_cb *cb);

//				pars_fsm_utils.c
bool			is_symbolic_tok(t_token_type tok_type);
bool			is_var(char *str, int *equal_pos);
bool			is_export(char *str);
t_redir_type	get_redir_type(t_token_type tok_type);
bool			is_quotes_close(char *str);

#endif
