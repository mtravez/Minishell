/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:10:55 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/29 21:03:37 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_back_inside_loop(char *word, t_quotes **quotes, size_t *i, size_t *j)
{
	char	c;

	if (word[(*i)] == '\'' || word[(*i)] == '\"')
	{
		if ((*j) < (*i))
			add_back(quotes, new_quote(NO_QUOTES, \
			ft_strndup(&word[(*j)], (*i) - (*j))));
		c = word[(*i)];
		*j = *i;
		while (word && word[++(*j)])
			if (word[(*j)] == c)
				return (c);
		return (c);
	}
	return (0);
}

char	*get_var_content_merged(char *expanded, t_envar *var)
{
	if (var->content)
		return (ft_strjoin_gnl(expanded, ft_strdup(var->content)));
	return (ft_strjoin_gnl(expanded, ft_strdup("")));
}

char	*delete_that_quote(char *quote, char *quote_less, int *i, int *j)
{
	char	c;

	if (quote[(*i)] == '\'' || quote[(*i)] == '\"')
	{
		if ((*i) > (*j))
			quote_less = ft_strjoin_gnl(quote_less, \
			ft_strndup(&quote[*j], (*i) - (*j)));
		c = quote[(*i)];
		*j = (*i) + 1;
		while (quote[*j] && quote[*j] != c)
			(*j)++;
		if ((*j) != (*i) + 1)
			quote_less = ft_strjoin_gnl(quote_less, \
			ft_strndup(&quote[(*i) + 1], (*j) - ((*i) + 1)));
		(*i) = ++(*j);
	}
	else
		(*i)++;
	return (quote_less);
}
