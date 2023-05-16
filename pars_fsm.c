
#include "pars_fsm.h"

void	parse_tokens(t_lexer *lexer)
{
	t_token				*token;
	enum e_states		state;
	enum e_states		new_state;

	state = LINE_STATE;
	new_state = state;
	token = lexer->token;
	if (!lexer)
		ft_printf("lexer error\n");
	while (state != END_STATE)
	{
		if (state == LINE_STATE || state == STR_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				ft_printf("state string:	%s\n", token->content);
				state = STR_STATE;
			}
			if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				ft_printf("state redir: %s\n", token->content);
				state = REDIR_STATE;
			}
			else
			{
				ft_printf("state error\n");
				break ;
			}
		}
		if (state == STR_STATE)
		{
			if (token->t_type == WORD_TOK || token->t_type == QUOTE_TOK)
			{
				;
			}
			if (token->t_type == PIPE)
			{
				ft_printf("state line: %s\n", token->content);
				state = LINE_STATE;
			}
			else
			{
				ft_printf("state error\n");
				break ;
			}
		}
		if (state == REDIR_STATE)
		{
			if (token->t_type == PIPE)
			{
				ft_printf("state line: %s\n", token->content);
				state = LINE_STATE;
			}
			else
			{
				ft_printf("state error\n");
				break ;
			}
		}
		else
		{
			ft_printf("state error\n");
			break ;
		}
		token = token->next_token;
		if (!token)
			state = END_STATE;
	}
}
