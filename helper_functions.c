#include "minishell.h"

size_t	ft_strstrlen(char **strstr)
{
	size_t	i;

	i = 0;
	while (strstr && strstr[i])
		i++;
	return (i);
}

char	**to_strstr(char *str)
{
	char	**strstr;

	strstr = malloc(sizeof(char *) * 2);
	strstr[0] = str;
	strstr[1] = NULL;
	return (strstr);
}

char	**ft_strstrjoin(char **str1, char **str2)
{
	char	**joint;
	int		i;
	int		j;

	if (!str1 && !str2)
		return (NULL);
	joint = malloc(
			sizeof(char *) * (ft_strstrlen(str1) + ft_strstrlen(str2) + 1));
	i = 0;
	while (str1 && str1[i])
	{
		joint[i] = str1[i];
		i++;
	}
	free(str1);
	j = 0;
	while (str2 && str2[j])
	{
		joint[i + j] = str2[j];
		j++;
	}
	free(str2);
	joint[i + j] = NULL;
	return (joint);
}

char	*ft_strndup(char *str, size_t n)
{
	size_t	i;
	char	*dupped;

	i = 0;
	dupped = malloc(n + 1);
	if (!dupped)
		return (NULL);
	while (str && str[i] && i < n)
	{
		dupped[i] = str[i];
		i++;
	}
	dupped[i] = '\0';
	return (dupped);
}

char	*ft_strchr_no_quotes(char *str, char c)
{
	int		i;
	char	quote;

	i = 0;
	while (str && str[i] && str[i] != c)
	{
		if (str[i] == '\'' || str[i] == '\'')
		{
			quote = str[i];
			while (str[i] && str[i] != quote)
				i++;
		}
		else
			i++;
	}
	if (str[i] && str[i] == c)
		return (&str[i]);
	return (NULL);
}
