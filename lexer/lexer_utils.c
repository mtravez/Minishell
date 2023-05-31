
#include "../minishell.h"

t_token_type	get_tok_type(char c)
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
	return (WORD_TOK);
}

t_token	*init_token(int size)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		ft_printf("token allocation failed\n");
		return (NULL);
	}
	token->content = malloc(size + 1);
	if (!token->content)
	{
		free(token);
		token = NULL;
		return (NULL);
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
	{
		ft_printf("lexer allocation failed\n");
		return (NULL);
	}
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
