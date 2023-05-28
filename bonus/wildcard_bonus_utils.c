
#include "../minishell.h"

int	compare_quotes(char *str1, char *str2)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	if (str1[i] == '\'' || str1[i] == '\"')
	{
		c = str1[i];
		i++;
	}
	else
		return (0);
	j = 0;
	while (str1[i] && str1[i] != c)
	{
		if (str1[i] != str2[j])
			return (0);
		i++;
		j++;
	}
	return (i + 1);
}

char	*get_prefix(char *address, int *index)
{
	int		i;
	int		j;
	char	*dir;

	i = 0;
	if (!address)
		return (NULL);
	dir = ft_strchr_no_quotes(address, '*');
	if (!dir)
		return (NULL);
	while (&address[i] != dir)
			i++;
	j = i;
	while (j >= 0)
	{
		if (address[j] == '/')
			break ;
		j--;
	}
	if (j < 0)
		return (ft_strdup(""));
	*index = j + 1;
	dir = ft_substr(address, 0, j + 1);
	return (remove_quotes(dir));
}

char	*get_word(char *wildcard, int *index)
{
	int		i;
	char	c;
	char	*word;

	i = 0;
	if (!wildcard || !wildcard[i])
		return (NULL);
	while (wildcard && wildcard[i] && wildcard[i] != '/')
	{
		if (wildcard[i] == '\'' || wildcard[i] == '\"')
		{
			c = wildcard[i];
			i++;
			while (wildcard[i] && wildcard[i] != c)
				i++;
		}
		i++;
	}
	word = ft_substr(wildcard, 0, i);
	*index = i;
	return (word);
}

int	skip_to_wildcard(int *i, int *j, char *wildcard, char *file)
{
	int	quotes;

	while (wildcard[*i] && file[*j] && wildcard[*i] != '*')
	{
		if (wildcard[*i] == '\'' || wildcard[*i] == '\"')
		{
			quotes = compare_quotes(&wildcard[*i], &file[*j]);
			if (!quotes)
				return (0);
			*i += quotes;
			*j += quotes - 2;
			return (1);
		}
		if (wildcard[(*i)++] != file[(*j)++])
			return (0);
	}
	return (1);
}
