
#include "pars_fsm.h"
#include "cmd_builder.h"
#include <stdlib.h>
#include <stdbool.h>

int	parse_tokens(t_lexer *lexer)
{
	t_token				*token;
	t_parser_state		state;
	t_parser_state		new_state;

	state = VAR_STATE;
	new_state = state;
	if (!lexer)
		ft_printf("lexer error\n");
	token = lexer->token;
	if (lexer->token_nr == 1 && is_symbolic_tok(token->t_type))
		return (EXIT_FAILURE);
	while (token)
	{
		if (state == VAR_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				if (is_var(token->content))
				{
					ft_printf("var --> var:	%s\n", token->content);
					token = token->next_token;
				}
				else
				{
					ft_printf("var --> argv:	%s\n", token->content);
					
					state = ARGV_STATE;
				}
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				ft_printf("var --> redir_start:	%s\n", token->content);
				state = REDIR_START_STATE;
				token = token->next_token;
			}
			else if (token->t_type == PIPE_TOK)
			{
				ft_printf("var --> var:	%s\n", token->content);
				token = token->next_token;
			}
			else
			{
				ft_printf("state var: error\n");
				break ;
			}
		}
		else if (state == ARGV_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("argv --> argv:	%s\n", token->content);
				state = ARGV_STATE;
			}
			else if (token->t_type == PIPE_TOK)
			{
				ft_printf("argv --> var:	%s\n", token->content);
				state = VAR_STATE;
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				ft_printf("argv --> redir:	%s\n", token->content);
				state = REDIR_STATE;
			}
			else
			{
				ft_printf("state argv: error\n");
				break ;
			}
			token = token->next_token;
		}
		else if (state == REDIR_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("redir --> argv:	%s\n", token->content);
				state = ARGV_STATE;
			}
			else
			{
				ft_printf("state redir: error\n");
				return (EXIT_FAILURE);
			}
			token = token->next_token;
		}
		else if (state == REDIR_START_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("redir_start --> var:	%s\n", token->content);
				state = VAR_STATE;
			}
			else
			{
				ft_printf("state redir_start: error\n");
				return (EXIT_FAILURE);
			}
			token = token->next_token;
		}
		else
			ft_printf("WTF\n");
	}
	return (0);
}
