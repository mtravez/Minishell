/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:35:49 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/30 12:38:37 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_type	get_tok_type(char c)
{
	if (c == PIPE_TOK)
		return (PIPE_TOK);
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
	return (WORD_TOK);
}

t_token	*init_token(int size)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		print_malloc_failed();
	token->content = malloc(size + 1);
	if (!token->content)
	{
		free(token);
		print_malloc_failed();
	}
	token->content[size] = 0;
	token->t_type = WORD_TOK;
	token->next_token = NULL;
	token->size = size;
	return (token);
}

t_lexer	*init_lexer(int size)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer) + sizeof(t_token));
	if (!lexer)
		print_malloc_failed();
	lexer->token_nr = 0;
	lexer->token = init_token(size);
	if (!lexer->token)
	{
		free(lexer);
		return (NULL);
	}
	return (lexer);
}

void	destroy_token(t_token **token)
{
	if (*token == NULL)
		return ;
	free((*token)->content);
	destroy_token(&(*token)->next_token);
	free(*token);
	*token = NULL;
}

void	destroy_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	destroy_token(&lexer->token);
	free(lexer);
}
