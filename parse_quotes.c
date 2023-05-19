#include "minishell.h"

int	has_quotes(char *word)
{
	return (ft_strchr(word, '\'') || ft_strchr(word, '\"'));
}

char	*join_var(char *str, t_envar **vars)
{
	int	i;
	int	j;
	t_envar	*var;
	char	*expanded;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	if (!str[i])
		return (ft_strdup(str));
	j = i + 1;
	while (str[j])
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			break ;
		j++;
	}
	expanded = ft_strndup(&str[i + 1], j - (i + 1));
	var = get_var(vars, expanded);
	free(expanded);
	if (!var)
		return (ft_strdup(""));
	expanded = ft_strndup(str, i);
	expanded = ft_strjoin_gnl(expanded, ft_strdup(var->content));
	if (j < ft_strlen(str))
		expanded = ft_strjoin_gnl(expanded, join_var(&str[j], vars));
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
		joint = ft_strjoin_gnl(joint, temp->content);
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
	int		i;
	int		j;
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
			j = i + 1;
			while (word && word[j])
			{
				if (word[j] == c)
					break ;
				j++;
			}
			break ;
		}
		i++;
	}
	if (i < j)
		add_back(quotes, new_quote(c, ft_strndup(&word[i + 1], j - (i + 1))));
	if (j < ft_strlen(word))
		split_quotes(&word[j + 1], quotes);
}

void	free_quotes(t_quotes *quote)
{
	if (!quote)
		return ;
	free_quotes(quote->next);
	free(quote);
}

/*This function expands variables and also removes quotes from a string.
@param word The String that holds the $ symbol that will be expanded
@param env The environment in Hash Table form*/
char	*expand_variables(char *word, t_envar **env)
{
	t_quotes	*list;
	char		*expanded;

	list = NULL;
	if (ft_strchr(word, '\'') || ft_strchr(word, '\"'))
		split_quotes(word, &list);
	else
		add_back(&list, new_quote(NO_QUOTES, ft_strdup(word)));
	expanded = expand(list, env);
	free_quotes(list);
	return (expanded);
}

// int main(int argc, char **argv, char **env)
// {
// 	char	*word = "hiiiii$USER<xd";
// 	t_envar **vars;
// 	vars = ft_calloc(sizeof(t_envar), ENVAR_ARRAY_SIZE);
// 	set_env(env, vars);
// 	printf("%s\n", word);
// 	char *hi = expand_variables(word, vars);
// 	printf("%s\n", hi);
// 	system("leaks a.out");
// }