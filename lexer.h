/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:42:21 by mtravez           #+#    #+#             */
/*   Updated: 2023/05/15 12:31:39 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

enum e_token_type
{
	PIPE_TOK = '|',
	AMPER_TOK = '&',
	LESS_TOK = '<',
	GREAT_TOK = '>',
	SPACE_TOK = ' ',
	NULL_TOK = '\0',
	DLESS_TOK,
	DGREAT_TOK,
	QUOTE_TOK,
	TOKEN_TOK = -1
};

typedef enum e_state
{
	STATE_DEFAULT,
	STATE_QUOTE
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
// t_lexer	*get_tokens(char *arg, int size);
t_lexer	*get_tokens(char *arg);

// lexer_utils.c
t_token	*init_token(int size);
t_lexer	*init_lexer(int size);
void	destroy_token(t_token **token);
void	destroy_lexer(t_lexer *lexer);
void	compress_lexer_less(t_lexer *lexer);
void	compress_lexer_great(t_lexer *lexer);

#endif