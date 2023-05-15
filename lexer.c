#include "minishell.h"

static char	get_tok_type(char c)
{
	if (c == PIPE_TOK)
		return (PIPE_TOK);
	if (c == AMPER_TOK)
		return (AMPER_TOK);
	if (c == '\'' || c == '\"')
		return (QUOTE_TOK);
	if (c == LESS_TOK)
		return (LESS_TOK);
	if (c == GREAT_TOK)
		return (GREAT_TOK);
	if (c == NULL_TOK)
		return (NULL_TOK);
	if (c == SPACE_TOK)
		return (SPACE_TOK);
	return (TOKEN_TOK);
}

t_token	*finish_token(t_token *token, int *index)
{
	if(*index)
	{
		token->content[*index] = 0;
		token->next_token = init_token(token->size - ft_strlen(token->content));
		*index = 0;
		return (token->next_token);
	}
	return (token);
}

int	add_to_token(t_token *token, char c, t_state *state, int index)
{
	char	c_type;

	c_type = get_tok_type(c);
	if (c_type == QUOTE_TOK)
		*state = STATE_QUOTE;
	else if (c_type == SPACE_TOK)
	{
		token = finish_token(token, &index);
		return (index);
	}
	else if (c_type == LESS_TOK)
	{
		if (token->t_type == LESS_TOK)
			token->t_type = DLESS_TOK;
		else
		{
			token = finish_token(token, &index);
			token->t_type = LESS_TOK;
		}
	}
	else if (c_type == GREAT_TOK)
	{
		if (token->t_type == GREAT_TOK)
			token->t_type = DGREAT_TOK;
		else
		{
			token = finish_token(token, &index);
			token->t_type = GREAT_TOK;
		}
	}
	else if (c_type != TOKEN_TOK)
	{
		token = finish_token(token, &index);
		token->content[index++] = c;
		token = finish_token(token, &index);
		return (0);
	}
	token->content[index] = c;
	return (index + 1);
}

void	create_tokens(t_token *token, char *arg)
{
	int		i;
	int		index;
	t_state	state;
	char	c;

	i = 0;
	index = 0;
	state = STATE_DEFAULT;
	while (arg[i])
	{
		if (state == STATE_QUOTE)
		{
			c = token->content[index - 1];
			token->t_type = QUOTE_TOK;
			while(arg[i] && arg[i] != c)
				token->content[index++] = arg[i++];
			if (arg[i])
				token->content[index++] = arg[i++];
		}
		if (!arg[i])
			break ;
		state = STATE_DEFAULT;
		if (state == STATE_DEFAULT)
		{
			index = add_to_token(token, arg[i], &state, index);
			i++;
			if (token->t_type == DGREAT_TOK || token->t_type == DLESS_TOK)
				finish_token(token, &index);
		}
		if (token->next_token && arg[i])
			token = token->next_token;
	}
	if (index)
		token->content[index] = 0;
	else
		destroy_token(&token->next_token);
}

int	get_size_tokens(t_token *token)
{
	int	i;
	t_token	*temp;

	i = 0;
	temp = token;
	while (temp)
	{
		i++;
		temp = temp->next_token;
	}
	return (i);
}

t_lexer	*get_tokens(char *argv)
{
	int		i;
	t_lexer	*lexer;

	i = 0;
	if (!argv || !argv[0])
		return (NULL);
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (0);
	lexer->token = init_token(ft_strlen(argv));
	create_tokens(lexer->token, argv);
	lexer->token_nr = get_size_tokens(lexer->token);
	return (lexer);
}