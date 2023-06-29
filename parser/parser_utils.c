/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:45:10 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/29 21:13:33 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>

bool	is_var(char *str, int *equal_pos)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			return (false);
		if (str[i] == '=')
		{
			*equal_pos = i;
			return (true);
		}
		i++;
	}
	return (false);
}

t_redir_type	get_redir_type(t_token_type tok_type)
{
	if (tok_type == LESS_TOK)
		return (IN_REDIR);
	if (tok_type == GREAT_TOK)
		return (OUT_REDIR);
	if (tok_type == DLESS_TOK)
		return (HEREDOC_REDIR);
	if (tok_type == DGREAT_TOK)
		return (APPEND_REDIR);
	return (IN_REDIR);
}

bool	is_quotes_close(char *str)
{
	int		i;
	int		s_count;
	int		d_count;

	i = 0;
	s_count = 0;
	d_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && s_count == 0 && d_count == 0)
			s_count = 1;
		else if (str[i] == '\'' && s_count == 1)
			s_count = 0;
		else if (str[i] == '"' && d_count == 0 && s_count == 0)
			d_count = 1;
		else if (str[i] == '"' && d_count == 1)
			d_count = 0;
		i++;
	}
	if (s_count == 1 || d_count == 1)
		return (false);
	return (true);
}
