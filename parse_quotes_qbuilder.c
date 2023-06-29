/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_qbuilder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:10:48 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/29 20:25:34 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

void	free_quotes(t_quotes *quote)
{
	if (!quote)
		return ;
	free(quote->content);
	free_quotes(quote->next);
	free(quote);
}

t_quotes	*new_quote(t_quote_type type, char *content)
{
	t_quotes	*quote;

	quote = malloc(sizeof(t_quotes));
	if (!quote)
		return (NULL);
	quote->is_quote = type;
	quote->content = content;
	quote->next = NULL;
	return (quote);
}

void	add_back(t_quotes **list, t_quotes *quote)
{
	t_quotes	*temp;

	temp = *list;
	if (!*list)
	{
		*list = quote;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = quote;
}

void	split_quotes(char *word, t_quotes **quotes)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	j = 0;
	c = '\0';
	while (word && word[i])
	{
		c = add_back_inside_loop(word, quotes, &i, &j);
		if (c)
			break ;
		i++;
	}
	if (i < j)
		add_back(quotes, new_quote(c, ft_strndup(&word[i], (j + 1) - i)));
	if (!word[i] && word[j])
		add_back(quotes, new_quote(NO_QUOTES, ft_strndup(&word[j], i - j)));
	else if (j < (ft_strlen(word) - 1))
		split_quotes(&word[j + 1], quotes);
}
