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

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	if (!str[i] || !is_var_char(str[i + 1]))
		return (str);
	expanded = get_var_name(&str[i + 1]);
	j = ft_strlen(expanded) + i + 1;
	var = get_var(vars, expanded);
	free(expanded);
	expanded = ft_strndup(str, i);
	if (var && var->content)
		expanded = ft_strjoin_gnl(expanded, ft_strdup(var->content));
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
	while (word && word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			if (j < i)
				add_back(quotes, new_quote(NO_QUOTES, ft_strndup(&word[j], i - j)));
			c = word[i];
			j = i;
			while (word && word[++j])
				if (word[j] == c)
					break ;
			break ;
		}
		i++;
	}
	if (i < j)
		add_back(quotes, new_quote(c, ft_strndup(&word[i], (j + 1) - i)));
	if (!word[i] && word[j])
		add_back(quotes, new_quote(NO_QUOTES, ft_strndup(&word[j], i - j)));
	else if (j < (ft_strlen(word) - 1))
		split_quotes(&word[j + 1], quotes);
}

char	*remove_quotes(char *quote)
{
	int		i;
	int		j;
	char	c;
	char	*quote_less;

	i = 0;
	j = 0;
	quote_less = NULL;
	while (quote && quote[i])
	{
		if (quote[i] == '\'' || quote[i] == '\"')
		{
			if (i > j)
				quote_less = ft_strjoin_gnl(quote_less, ft_strndup(&quote[j], i - j));
			c = quote[i];
			j = i + 1;
			while (quote[j] && quote[j] != c)
				j++;
			if (j != i + 1)
				quote_less = ft_strjoin_gnl(quote_less, ft_strndup(&quote[i + 1], j - (i + 1)));
			i = ++j;
		}
		else
			i++;
	}
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