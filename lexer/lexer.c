#include "../minishell.h"

t_token	*finish_token(t_token *token, int *index)
{
	if (*index)
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
	if (c_type == SPACE_TOK)
		return (space_condition(token, index));
	else if (c_type == LESS_TOK || c_type == GREAT_TOK)
		token = less_great_condition(token, c, &index);
	else if (c_type != WORD_TOK && c_type != QUOTE_TOK)
		return (no_word_no_quote_condition(token, c, &index));
	if ((token->t_type == LESS_TOK || token->t_type == GREAT_TOK) && \
	(c_type != LESS_TOK && c_type != GREAT_TOK))
		token = less_great_finish_condition(token, &index);
	if (c_type == QUOTE_TOK)
		quote_condition(token, state);
	token->content[index] = c;
	return (index + 1);
}

int	quote_state(int *toki, int *stri, t_token *token, char *arg)
{
	char	c;

	c = token->content[(*toki) - 1];
	token->t_type = QUOTE_TOK;
	while (arg[(*stri)] && arg[(*stri)] != c)
		token->content[(*toki)++] = arg[(*stri)++];
	if (arg[(*stri)])
		token->content[(*toki)++] = arg[(*stri)++];
	return (arg[*stri]);
}

void	create_tokens(t_token *token, char *arg)
{
	int		i;
	int		index;
	t_state	state;

	i = 0;
	index = 0;
	state = STATE_DEFAULT;
	while (arg[i])
	{
		if (state == STATE_QUOTE && !quote_state(&index, &i, token, arg))
			break ;
		state = STATE_DEFAULT;
		index = add_to_token(token, arg[i], &state, index);
		i++;
		if (token->t_type == DGREAT_TOK || token->t_type == DLESS_TOK)
			finish_token(token, &index);
		while (token->next_token && arg[i])
			token = token->next_token;
	}
	if (index)
		token->content[index] = 0;
	else
		destroy_token(&token->next_token);
}

t_lexer	*get_tokens(char *argv)
{
	int		i;
	t_lexer	*lexer;
	t_token	*temp;
	char	*line;

	i = 0;
	if (!argv || !argv[0])
		return (NULL);
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (0);
	line = ft_strtrim(argv, " ");
	lexer->token = init_token(ft_strlen(line));
	create_tokens(lexer->token, line);
	lexer->token_nr = 0;
	temp = lexer->token;
	while (temp)
	{
		lexer->token_nr++;
		temp = temp->next_token;
	}
	free(line);
	return (lexer);
}
