/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:44:01 by mtravez           #+#    #+#             */
/*   Updated: 2023/05/12 17:33:31 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	token->t_type = TOKEN_TOK;
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

void	compress_lexer_less(t_lexer *lexer)
{
	t_token	*last;
	t_token	*temp;

	if (!lexer)
		return ;
	temp = lexer->token;
	while (temp)
	{
		if (temp->t_type == LESS_TOK)
		{
			last = temp;
			temp = temp->next_token;
			if (temp && temp->t_type == LESS_TOK)
			{
				free(last->content);
				last->content = ft_strdup("<<");
				last->t_type = DLESS_TOK;
				last->next_token = temp->next_token;
				free(temp->content);
				free(temp);
				temp = last;
			}
		}
		else
			temp = temp->next_token;
	}
}

void	compress_lexer_great(t_lexer *lexer)
{
	t_token	*last;
	t_token	*temp;

	if (!lexer)
		return ;
	temp = lexer->token;
	while (temp)
	{
		if (temp->t_type == GREAT_TOK)
		{
			last = temp;
			temp = temp->next_token;
			if (temp && temp->t_type == GREAT_TOK)
			{
				free(last->content);
				last->content = ft_strdup(">>");
				last->t_type = DGREAT_TOK;
				last->next_token = temp->next_token;
				free(temp->content);
				free(temp);
				temp = last;
			}
		}
		else
			temp = temp->next_token;
	}
}
