/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:44:37 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/29 22:38:19 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builder.h"

void	give_argv_to_cb(
	t_cb *cb, t_token *token, t_envar **env)
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

void	give_redir_to_cb(
	t_cb *cb, t_token *token, t_envar **env, t_redir_type redir_type)
{
	char			*str_dup;

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
