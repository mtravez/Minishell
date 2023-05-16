
#ifndef PARS_FSM_H
# define PARS_FSM_H

# include "minishell.h"

/*
@startuml
state line
state string
state argv
state var
state redir
line --> string: WORD, QUOTE
line --> redir: LESS, GREAT, DLESS, DGREAT
string --> var: str(=)
string --> argv: str
string --> line: PIPE
redir --> string: WORD, QUOTE
redir --> line: PIPE
var --> line: PIPE
var --> redir: LESS, GREAT, DLESS, DGREAT
var --> string: WORD, QUOTE
argv --> redir: LESS, GREAT, DLESS, DGREAT
argv --> argv: WORD, QUOTE
argv --> line: PIPE
@enduml
*/
/*
	PIPE_TOK

	WORD_TOK
	QUOTE_TOK

	LESS_TOK
	GREAT_TOK
	DLESS_TOK
	DGREAT_TOK
*/
enum e_states
{
	LINE_STATE,
	STR_STATE,
	ARGV_STATE,
	VAR_STATE,
	REDIR_STATE,
	END_STATE,
};

enum e_redir_type
{
	LESS_REDIR,
	GREAT_REDIR,
	DLESS_REDIR,
	DGREAT_REDIRE
};

typedef struct s_redirs_list
{
	enum e_redir_type	redir_type;
	char				*word;
}	t_redirs;

typedef struct s_variables_list
{
	char	*name;
	char	*value;
}	t_vars_list;

typedef char	*t_words_list;

typedef struct s_commands
{
	t_redirs		redirs;
	t_vars_list		vars;
	t_words_list	words;
}	t_cmds;

typedef struct s_commands_list
{
	t_cmds					command;
	struct s_cmd_list		*next;
}	t_cmd_list;

typedef struct s_line
{
	t_cmd_list	cmds;
}	t_line;

void	parse_tokens(t_lexer *lexer);

#endif
