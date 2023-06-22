#include "../minishell.h"

int	space_condition(t_token *token, int index)
{
	finish_token(token, &index);
	return (index);
}

t_token	*less_great_condition(t_token *token, char c, int *index)
{
	char	c_type;

	c_type = get_tok_type(c);
	if (c_type == LESS_TOK)
	{
		if (token->t_type == LESS_TOK)
			token->t_type = DLESS_TOK;
		else
		{
			token = finish_token(token, index);
			token->t_type = LESS_TOK;
		}
	}
	else if (c_type == GREAT_TOK)
	{
		if (token->t_type == GREAT_TOK)
			token->t_type = DGREAT_TOK;
		else
		{
			token = finish_token(token, index);
			token->t_type = GREAT_TOK;
		}
	}
	return (token);
}

int	no_word_no_quote_condition(t_token *token, char c, int *index)
{
	// printf("%c, %i\n", c, *index);
	token = finish_token(token, index);
	token->t_type = get_tok_type(c);
	token->content[(*index)++] = c;
	token = finish_token(token, index);
	return (0);
}

t_token	*less_great_finish_condition(t_token *token, int *index)
{
	*index = 1;
	return (finish_token(token, index));
}

void	quote_condition(t_token *token, t_state *state)
{
	token->t_type = QUOTE_TOK;
	*state = STATE_QUOTE;
}
