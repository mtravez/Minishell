
#include "../minishell.h"

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

char	*get_prefix(char *address, int *index)
{
	int		i;
	int		j;
	char	*dir;

	i = 0;
	if (!address)
		return (NULL);
	dir = ft_strchr(address, '*');
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
	return (ft_substr(address, 0, j + 1));
}

char	*get_word(char *wildcard, int *index)
{
	int		i;
	char	*word;

	i = 0;
	if (!wildcard || !wildcard[i])
		return (NULL);
	while (wildcard && wildcard[i] && wildcard[i] != '/')
		i++;
	word = ft_substr(wildcard, 0, i);
	*index = i;
	return (word);
}

int	compare_wild(char *wildcard, char *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!wildcard || !file || !ft_strncmp(file, ".", 2) || !ft_strncmp(file, "..", 3))
		return (0);
	while (wildcard[i] && file[j] && wildcard[i] != '*')
		if (wildcard[i++] != file[j++])
			return (0);
	if (!wildcard[i] && !file[j])
		return (1);
	while (file[j])
	{
		if (wildcard[i] == '*')
		{
			if (!wildcard[++i])
				return (1);
			j--;
		}
		else if (wildcard[i] == file[j])
			if (compare_wild(&wildcard[i], &file[j]))
				return (1);
		j++;
	}
	return (0);
}

/*This function expands a wildcard. The prefix should be a
malloced empty string, while the suffix should be the wildcard string.
Both of these parameters will be freed inside the function.*/
char	**expand_wildcard(char *prefix, char *suffix)
{
	char			*subdir;
	DIR				*src_dir;
	struct dirent	*dent;
	char			**string;
	int				i;
	char			*address;

	i = 0;
	prefix = ft_strjoin_gnl(prefix, get_prefix(suffix, &i));
	suffix = ft_strndup(&suffix[i], ft_strlen(&suffix[i]));
	subdir = get_word(suffix, &i);
	if (prefix[0])
		src_dir = opendir(prefix);
	else
		src_dir = opendir(".");
	if (!src_dir)
	{
		free(prefix);
		free(suffix);
		return (NULL);
	}
	dent = readdir(src_dir);
	string = NULL;
	while (dent)
	{
		if ((ft_strchr(suffix, '/') && dent->d_type == DT_DIR) \
		&& compare_wild(subdir, dent->d_name))
		{
			address = ft_strjoin(prefix, dent->d_name);
			string = ft_strstrjoin(string, \
			expand_wildcard(address, &suffix[i]));
		}
		else if (!ft_strchr(suffix, '/') && compare_wild(subdir, dent->d_name))
		{
			address = ft_strjoin(prefix, dent->d_name);
			string = ft_strstrjoin(string, to_strstr(address));
		}
		dent = readdir(src_dir);
	}
	closedir(src_dir);
	free(suffix);
	free(prefix);
	free(subdir);
	return (string);
}

// int main(void)
// {
// 	char	*prefix = ft_strdup("");
// 	char	*suffix = ft_strdup("/Users/mtravez/Documents/42/Random/testing_wildcrds/ft*/*hi*.*");
// 	char	**str = expand_wildcard(prefix, suffix);
// 	int	i = 0;
// 	while (str && str[i])
// 	{
// 		printf("%s\n", str[i]);
// 		i++;
// 	}
// 	free_array(str);
// 	system("leaks a.out");
// 	return (0);
// }