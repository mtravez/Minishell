/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:25:52 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/29 21:03:48 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (ft_strdup(str));
	if (ft_isdigit(str[i]))
	{
		while (str && str[i] && ft_isdigit(str[i]))
			i++;
		if (str[i])
			return (ft_strndup(str, i));
	}
	while (str && str[i])
	{
		if (str[i] == '?' && i == 0)
		{
			i++;
			break ;
		}
		else if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		i++;
	}
	return (ft_strndup(str, i));
}

char	*join_var(char *str, t_envar **vars)
{
	size_t	i;
	size_t	j;
	t_envar	*var;
	char	*expanded;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			break ;
	if (!str[i] || !is_var_char(str[i + 1]))
		return (str);
	expanded = get_var_name(&str[i + 1]);
	j = ft_strlen(expanded) + i + 1;
	var = get_var(vars, expanded);
	free(expanded);
	expanded = ft_strndup(str, i);
	if (var)
		expanded = get_var_content_merged(expanded, var);
	if (j < ft_strlen(str))
		expanded = ft_strjoin_gnl(expanded, join_var(ft_strdup(&str[j]), vars));
	free(str);
	return (expanded);
}

char	*expand(t_quotes *quote, t_envar **vars)
{
	char		*joint;
	t_quotes	*temp;

	temp = quote;
	joint = NULL;
	while (temp)
	{
		if (ft_strchr(temp->content, '$') && temp->is_quote != QUOTES)
			temp->content = join_var(temp->content, vars);
		temp = temp->next;
	}
	temp = quote;
	while (temp)
	{
		joint = ft_strjoin_gnl(joint, ft_strdup(temp->content));
		temp = temp->next;
	}
	return (joint);
}

char	*remove_quotes(char *quote)
{
	int		i;
	int		j;
	char	*quote_less;

	i = 0;
	j = 0;
	quote_less = NULL;
	while (quote && quote[i])
		quote_less = delete_that_quote(quote, quote_less, &i, &j);
	quote_less = ft_strjoin_gnl(quote_less, ft_strndup(&quote[j], i - j));
	free(quote);
	return (quote_less);
}

/*This function expands variables and also removes quotes from a string.
@param word The String that holds the $ symbol that will be expanded
@param env The environment in Hash Table form*/
char	**expand_variables(char *word, t_envar **env)
{
	t_quotes	*list;
	char		*expanded;
	char		**wild_expand;

	list = NULL;
	wild_expand = NULL;
	if (ft_strchr(word, '\'') || ft_strchr(word, '\"'))
		split_quotes(word, &list);
	else
		add_back(&list, new_quote(NO_QUOTES, ft_strdup(word)));
	expanded = expand(list, env);
	free_quotes(list);
	if (ft_strchr_no_quotes(expanded, '*'))
		wild_expand = expand_wildcard(ft_strdup(""), expanded);
	if (!wild_expand)
		wild_expand = to_strstr(remove_quotes(ft_strdup(expanded)));
	free(expanded);
	return (wild_expand);
}

// int main(int argc, char **argv, char **env)
// {
// 	argc = 0;
// 	argv = (void *) argv;

// 	char *hi = "$\"hello\"$hi\"$hiiii\"";
// 	t_envar **env_vars = ft_calloc(ENVAR_ARRAY_SIZE, sizeof(t_envar *));
// 	set_env(env, env_vars);
// 	char **expanded = expand_variables(hi, env_vars);
// 	int i = 0;
// 	while (expanded[i])
// 	{
// 		printf("%s\n", expanded[i]);
// 		i++;
// 	}
// 	free_array(expanded);
// 	free_hash_list(env_vars);
// 	return (0);
// }