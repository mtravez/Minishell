
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
		if (state == LINE_STATE || state == CMDS_STATE)
		{
			if (token->t_type == TOKEN_TOK
				|| token->t_type == QUOTE_TOK
				|| token->t_type == DB_QUOTE_TOK)
			{
				ft_printf("state cmds:	%s\n", token->content);
				state = CMDS_STATE;
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
