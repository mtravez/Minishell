
#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>

typedef enum e_token_type
{
	PIPE_TOK = '|',
	AMPER_TOK = '&',
	LESS_TOK = '<',
	GREAT_TOK = '>',
	SPACE_TOK = ' ',
	NULL_TOK = '\0',
	DLESS_TOK,
	DGREAT_TOK,
	QUOTE_TOK,
	WORD_TOK = -1
}	t_token_type;

typedef enum e_state
{
	STATE_DEFAULT,
	STATE_QUOTE
}	t_state;

typedef struct s_token
{
	t_token_type	t_type;
	char			*content;
	struct s_token	*next_token;
	size_t			size;
}	t_token;

typedef struct s_lexer
{
	t_token	*token;
	int		token_nr;
}	t_lexer;

// lexer.c
// t_lexer	*get_tokens(char *arg, int size);
t_lexer			*get_tokens(char *arg);
t_token_type	get_tok_type(char c);

// lexer_utils.c
t_token			*init_token(int size);
t_lexer			*init_lexer(int size);
void			destroy_token(t_token **token);
void			destroy_lexer(t_lexer *lexer);
t_token			*finish_token(t_token *token, int *index);
int				space_condition(t_token *token, int index);
t_token			*less_great_condition(t_token *token, char c, int *index);
int				no_word_no_quote_condition(t_token *token, char c, int *index);
t_token			*less_great_finish_condition(t_token *token, int *index);
void			quote_condition(t_token *token, t_state *state);

#endif