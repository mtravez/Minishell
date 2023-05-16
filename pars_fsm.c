
#include "pars_fsm.h"
#include <stdlib.h>
#include <stdbool.h>

bool	if_symbolic_tok(t_token_type tok_type)
{
	if (tok_type == PIPE_TOK)
		ft_printf("syntax error near unexpected token `|'\n");
	else if (tok_type == LESS_TOK || tok_type == DLESS_TOK
		|| tok_type == GREAT_TOK || tok_type == DGREAT_TOK)
		ft_printf("syntax error near unexpected token `newline'\n");
	else
		return (false);
	return (true);
}

// return equal position
bool	if_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	parse_tokens(t_lexer *lexer)
{
	t_token				*token;
	t_parser_state		state;
	t_parser_state		new_state;

	state = LINE_STATE;
	new_state = state;
	token = lexer->token;
	if (!lexer)
		ft_printf("lexer error\n");
	if (lexer->token_nr == 1 && if_symbolic_tok(token->t_type))
		return (EXIT_FAILURE);
	while (state != END_STATE)
	{
		if (state == LINE_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("state string:	%s\n", token->content);
				state = STR_STATE;
				if (if_var(token->content))
				{
					ft_printf("state var:	%s\n", token->content);
					state = VAR_STATE;
				}
				else
				{
					ft_printf("state argv:	%s\n", token->content);
					state = ARGV_STATE;
				}
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				ft_printf("state redir:	%s\n", token->content);
				state = REDIR_STATE;
			}
			else
			{
				ft_printf("state line: error\n");
				break ;
			}
		}
		else if (state == STR_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("state string:	%s\n", token->content);
				state = STR_STATE;
			}
			else if (token->t_type == PIPE_TOK)
			{
				ft_printf("state line: %s\n", token->content);
				state = LINE_STATE;
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				ft_printf("state redir:	%s\n", token->content);
				state = REDIR_STATE;
			}
		}
		else if (state == VAR_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("state string:	%s\n", token->content);
				state = STR_STATE;
			}
			else if (token->t_type == PIPE_TOK)
			{
				ft_printf("state line: %s\n", token->content);
				state = LINE_STATE;
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				ft_printf("state redir:	%s\n", token->content);
				state = REDIR_STATE;
			}
		}
		else if (state == ARGV_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("state argv:	%s\n", token->content);
				state = ARGV_STATE;
			}
			else if (token->t_type == PIPE_TOK)
			{
				ft_printf("state line: %s\n", token->content);
				state = LINE_STATE;
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				ft_printf("state redir:	%s\n", token->content);
				state = REDIR_STATE;
			}
		}
		else if (state == REDIR_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("state redir:	%s\n", token->content);
				state = REDIR_STATE;
			}
			else if (token->t_type == PIPE_TOK)
			{
				ft_printf("state line: %s\n", token->content);
				state = LINE_STATE;
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				ft_printf("state redir:	%s\n", token->content);
				state = REDIR_STATE;
			}
		}
		else
			ft_printf("WTF\n");
		token = token->next_token;
		if (!token)
			state = END_STATE;
	}
	return (0);
}
