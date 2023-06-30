/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:39:27 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 15:31:15 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cmd_builder.h"
#include <stdio.h>
#include <stdbool.h>

int	parse_tokens(t_lexer *lexer, t_cb *cb, t_envar **env)
{
	t_pars	pars;

	if (init_t_pars(&pars, lexer, &cb))
		return (EXIT_FAILURE);
	while (pars.token)
	{
		if (pars.state == VAR_STATE)
		{
			if (if_var_state(&pars, &cb, env))
				return (EXIT_FAILURE);
		}
		else if (pars.state == ARGV_STATE)
		{
			if (if_argv_state(&pars, &cb, env))
				return (EXIT_FAILURE);
		}
		else if (pars.state == REDIR_STATE || pars.state == REDIR_START_STATE)
		{
			if (if_redir_state(&pars, &cb, env))
				return (EXIT_FAILURE);
		}
		else
			return (print_syn_error(&cb));
	}
	return (EXIT_SUCCESS);
}

int	init_t_pars(t_pars *pars, t_lexer *lexer, t_cb **cb)
{
	if (!lexer)
	{
		perror("lexer error\n");
		return (EXIT_FAILURE);
	}
	pars->token = lexer->token;
	pars->state = VAR_STATE;
	**cb = cb_init();
	return (EXIT_SUCCESS);
}

int	if_var_state(t_pars *pars, t_cb **cb, t_envar **env)
{
	if (pars->token->t_type == WORD_TOK || (pars->token->t_type == QUOTE_TOK
			&& is_quotes_close(pars->token->content)))
	{
		if (give_var_to_cb(pars, cb, env))
			return (EXIT_FAILURE);
	}
	else if (pars->token->t_type == LESS_TOK || pars->token->t_type == GREAT_TOK
		|| pars->token->t_type == DLESS_TOK
		|| pars->token->t_type == DGREAT_TOK)
	{
		pars->state = REDIR_START_STATE;
		pars->redir_type = get_redir_type(pars->token->t_type);
		if (pars->token->next_token == NULL)
			return (print_syn_error(cb));
		else
			pars->token = pars->token->next_token;
	}
	else if (pars->token->t_type == PIPE_TOK)
	{
		if (if_pipe(pars, cb))
			return (EXIT_FAILURE);
	}
	else
		return (print_syn_error(cb));
	return (EXIT_SUCCESS);
}

int	give_var_to_cb(t_pars *pars, t_cb **cb, t_envar **env)
{
	int		equal_pos;

	if (is_var(pars->token->content, &equal_pos))
	{
		cb_add_var(cb, pars->token->content, equal_pos, env);
		pars->token = pars->token->next_token;
	}
	else
		pars->state = ARGV_STATE;
	return (EXIT_SUCCESS);
}

char	*str_char_join(char const *s1, char const *s2, char c)
{
	char	*joint;
	size_t	sizes1;
	size_t	sizes2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	joint = malloc(sizes1 + sizes2 + 2);
	if (!joint)
		print_malloc_failed();
	ft_memcpy(joint, s1, sizes1);
	joint[sizes1] = c;
	ft_memcpy(joint + sizes1 + 1, s2, sizes2);
	joint[sizes1 + sizes2 + 1] = '\0';
	return (joint);
}
