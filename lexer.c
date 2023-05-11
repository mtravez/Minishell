/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:30:29 by mtravez           #+#    #+#             */
/*   Updated: 2023/05/11 13:03:32 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	get_tok_type(char c)
{
	if (c == PIPE_TOK)
		return (PIPE_TOK);
	if (c == AMPER_TOK)
		return (AMPER_TOK);
	if (c == QUOTE_TOK)
		return (QUOTE_TOK);
	if (c == DB_QUOTE_TOK)
		return (DB_QUOTE_TOK);
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

static int	add_to_token(t_token *token, char c, int index, t_state *state)
{
	char	c_type;

	c_type = get_tok_type(c);
	if (*state == STATE_DEFAULT)
	{
		if (c_type == DB_QUOTE_TOK)
			*state = STATE_DB_QUOTE;
		else if (c_type == QUOTE_TOK)
			*state = STATE_QUOTE;
		else if (c_type == SPACE_TOK)
		{
			if (index)
			{
				token->content[index] = 0;
				token->next_token = init_token(token->size - \
				ft_strlen(token->content));
				token = token->next_token;
			}
			return (0);
		}
		else if (c_type != TOKEN_TOK)
		{
			if (index)
			{
				token->content[index] = 0;
				token->next_token = init_token(token->size - \
				ft_strlen(token->content));
				token = token->next_token;
			}
			token->content[0] = c;
			token->content[1] = 0;
			token->t_type = c_type;
			token->next_token = init_token(token->size - \
			ft_strlen(token->content));
			token = token->next_token;
			return (0);
		}
		token->content[index] = c;
		return (index + 1);
	}
	if (*state == STATE_DB_QUOTE)
	{
		token->content[index] = c;
		token->t_type = DB_QUOTE_TOK;
		if (c_type == DB_QUOTE_TOK)
			*state = STATE_DEFAULT;
		return (index + 1);
	}
	if (*state == STATE_QUOTE)
	{
		token->content[index] = c;
		token->t_type = QUOTE_TOK;
		if (c_type == QUOTE_TOK)
			*state = STATE_DEFAULT;
		return (index + 1);
	}
	return (index + 1);
}

static void	tokenize(t_lexer *lexer, int j, char *arg)
{
	t_token		*token;
	size_t		i;
	t_state		state;

	token = lexer->token;
	i = 0;
	state = STATE_DEFAULT;
	while (arg && arg[i] && i < lexer->token->size)
	{
		j = add_to_token(token, arg[i++], j, &state);
		if (!j && i < lexer->token->size)
		{
			while (token->next_token)
			{
				token = token->next_token;
				lexer->token_nr++;
			}
		}
	}
	if (j)
		token->content[j] = 0;
	else
		destroy_token(&token->next_token);
}

t_lexer	*get_tokens(char *arg, int size)
{
	t_lexer	*lexer;
	t_token	*token;
	int		index;

	lexer = init_lexer(size);
	if (!lexer)
		return (NULL);
	token = lexer->token;
	lexer->token_nr++;
	index = 0;
	tokenize(lexer, index, arg);
	return (lexer);
}
