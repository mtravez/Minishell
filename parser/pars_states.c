/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:44:37 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/18 19:57:22 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builder.h"

int	if_argv_state(t_pars *pars, t_cb **cb, t_envar **env)
{
	if (pars->token->t_type == WORD_TOK || (pars->token->t_type == QUOTE_TOK
			&& is_quotes_close(pars->token->content)))
	{
		give_argv_to_cb(cb, pars->token, env);
		pars->state = ARGV_STATE;
	}
	else if (pars->token->t_type == PIPE_TOK)
	{
		if (if_pipe(pars, cb))
			return (EXIT_FAILURE);
	}
	else if (pars->token->t_type == LESS_TOK || pars->token->t_type == GREAT_TOK
		|| pars->token->t_type == DLESS_TOK
		|| pars->token->t_type == DGREAT_TOK)
	{
		pars->redir_type = get_redir_type(pars->token->t_type);
		pars->state = REDIR_STATE;
		if (pars->token->next_token == NULL)
			return (print_syn_error(cb));
	}
	else
		return (print_syn_error(cb));
	pars->token = pars->token->next_token;
	return (EXIT_SUCCESS);
}

int	if_pipe(t_pars *pars, t_cb **cb)
{
	if (!pars->token->next_token
		|| pars->token->next_token->t_type == PIPE_TOK)
		return (print_syn_error(cb));
	else
	{
		cb_add_cmd_node(cb);
		pars->state = VAR_STATE;
	}
	return (EXIT_SUCCESS);
}

void	give_argv_to_cb(
	t_cb **cb, t_token *token, t_envar **env)
{
	char	**expanded;
	char	**orig_expanded;

	expanded = expand_variables(token->content, env);
	orig_expanded = expanded;
	while (*expanded)
	{
		if (ft_strlen(*expanded) != 0)
			cb_add_argv(cb, *expanded);
		free(*expanded);
		expanded++;
	}
	free(orig_expanded);
}

int	if_redir_state(t_pars *pars, t_cb **cb, t_envar **env)
{
	if (pars->token->t_type == WORD_TOK || (pars->token->t_type == QUOTE_TOK
			&& is_quotes_close(pars->token->content)))
		give_redir_to_cb(cb, pars->token, env, pars->redir_type);
	else
		return (print_syn_error(cb));
	if (pars->state == REDIR_STATE)
		pars->state = ARGV_STATE;
	else
		pars->state = VAR_STATE;
	pars->token = pars->token->next_token;
	return (EXIT_SUCCESS);
}

void	give_redir_to_cb(
	t_cb **cb, t_token *token, t_envar **env, t_redir_type redir_type)
{
	char	*str_dup;

	str_dup = ft_strdup(token->content);
	if (redir_type == HEREDOC_REDIR && token->t_type == QUOTE_TOK)
	{
		str_dup = remove_quotes(str_dup);
		cb_add_redir(cb, str_dup, redir_type, env);
	}
	else
		cb_add_redir(cb, str_dup, redir_type, env);
	free(str_dup);
}
