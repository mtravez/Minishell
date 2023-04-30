/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:42:21 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/30 11:51:56 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

enum e_token_type
{
	PIPE_TOK = '|',
	AMPER_TOK = '&',
	QUOTE_TOK = '\'',
	DB_QUOTE_TOK = '\"',
	LESS_TOK = '<',
	GREAT_TOK = '>',
	SPACE_TOK = ' ',
	NULL_TOK = '\0',
	TOKEN_TOK = -1
};

typedef enum e_state
{
	STATE_DEFAULT,
	STATE_QUOTE,
	STATE_DB_QUOTE
}	t_state;

typedef struct s_token
{
	int				t_type;
	char			*content;
	struct s_token	*next_token;
	size_t			size;
}	t_token;

typedef struct s_lexer
{
	t_token	*token;
	int		token_nr;
}	t_lexer;

// lexer.c
t_lexer	*get_tokens(char *arg, int size);

// lexer_utils.c
t_token	*init_token(int size);
t_lexer	*init_lexer(int size);
void	destroy_token(t_token **token);
void	destroy_lexer(t_lexer *lexer);

#endif