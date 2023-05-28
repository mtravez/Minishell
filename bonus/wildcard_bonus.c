#include "../minishell.h"

int	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

int	compare_wild(char *wildcard, char *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!wildcard || !file || !ft_strncmp(file, ".", 2) \
	|| !ft_strncmp(file, "..", 3) || !skip_to_wildcard(&i, &j, wildcard, file))
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
		else if (wildcard[i] == file[j] || is_quotes(wildcard[i]))
			if (compare_wild(&wildcard[i], &file[j]))
				return (1);
		j++;
	}
	return (0);
}

void	assign_prefix_suffix(char **prefix, char **suffix)
{
	int	i;

	i = 0;
	*prefix = ft_strjoin_gnl(*prefix, get_prefix(*suffix, &i));
	*suffix = ft_strndup(&suffix[i], ft_strlen(&suffix[i]));
}

/*This function expands a wildcard. The prefix should be a
malloced empty string, while the suffix should be the wildcard string.*/
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
	subdir = get_word(suffix, &i);
	dent = readdir(src_dir);
	string = NULL;
	while (dent)
	{
		if ((ft_strchr_no_quotes(suffix, '/') && dent->d_type == DT_DIR) \
		&& compare_wild(subdir, dent->d_name))
		{
			address = ft_strjoin(prefix, dent->d_name);
			string = ft_strstrjoin(string, \
			expand_wildcard(address, &suffix[i]));
		}
		else if (!ft_strchr_no_quotes(suffix, '/') && compare_wild(subdir, dent->d_name))
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

// char	**test(char *prefix, char *suffix)
// {
// 	char	**str = expand_wildcard(prefix, suffix);
// 	int	i = 0;
// 	while (str && str[i])
// 	{
// 		printf("%s\n", str[i]);
// 		i++;
// 	}
// 	return (str);
// }

// int main(void)
// {
// 	char	*prefix = ft_strdup("");
// 	char	*suffix = ft_strdup("*");
// 	char **str = test(prefix, suffix);
// 	system("leaks a.out");
// 	return (0);
// // cc wildcard_bonus.c wildcard_bonus_utils.c ../environment/env_utils.c ../environment/env_vars.c ../libft/libft.a 
// }