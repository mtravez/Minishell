#include "../minishell.h"

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
		else if (wildcard[i] == file[j] || \
		wildcard[i] == '\'' || wildcard[i] == '\"')
			if (compare_wild(&wildcard[i], &file[j]))
				return (1);
		j++;
	}
	return (0);
}

int	start_vars(char	**prefix, char **suffix, t_wildir **wild, int *i)
{
	*prefix = ft_strjoin_gnl(*prefix, get_prefix(*suffix, i));
	*suffix = ft_strndup(&(*suffix)[*i], ft_strlen(&(*suffix)[*i]));
	*wild = malloc(sizeof(t_wildir));
	if (!*wild)
		return (0);
	if ((*prefix)[0])
		(*wild)->src_dir = opendir(*prefix);
	else
		(*wild)->src_dir = opendir(".");
	if (!(*wild)->src_dir)
	{
		free(*prefix);
		free(*suffix);
		free(*wild);
		return (0);
	}
	(*wild)->subdir = get_word(*suffix, i);
	(*wild)->dent = readdir((*wild)->src_dir);
	return (1);
}

void	free_wild(char *prefix, char *suffix, t_wildir *wild)
{
	closedir(wild->src_dir);
	free(suffix);
	free(prefix);
	free(wild->subdir);
	free(wild);
}

char	**verify_file(char *prefix, char *suffix, t_wildir *wild, int *i)
{
	if ((ft_strchr_no_quotes(suffix, '/') && wild->dent->d_type == DT_DIR) \
		&& compare_wild(wild->subdir, wild->dent->d_name))
	{
		wild->address = ft_strjoin(prefix, wild->dent->d_name);
		return (expand_wildcard(wild->address, &suffix[*i]));
	}
	else if (!ft_strchr_no_quotes(suffix, '/') && \
	compare_wild(wild->subdir, wild->dent->d_name))
	{
		wild->address = ft_strjoin(prefix, wild->dent->d_name);
		return (to_strstr(wild->address));
	}
	return (NULL);
}

/*This function expands a wildcard. The prefix should be a
malloced empty string, while the suffix should be the wildcard string.*/
char	**expand_wildcard(char *prefix, char *suffix)
{
	char		**string;
	int			i;
	t_wildir	*wild;

	i = 0;
	if (!start_vars(&prefix, &suffix, &wild, &i))
		return (NULL);
	string = NULL;
	while (wild->dent)
	{
		string = ft_strstrjoin(string, verify_file(prefix, suffix, wild, &i));
		wild->dent = readdir(wild->src_dir);
	}
	free_wild(prefix, suffix, wild);
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
// 	char	*suffix = ft_strdup("/Users/mtravez/Documents/42/Random/testing_wildcrds/ft*h*/*.*");
// 	char **str = test(prefix, suffix);
// 	free_array(str);
// 	// system("leaks a.out");
// 	return (0);
// // cc wildcard_bonus.c wildcard_bonus_utils.c ../environment/env_utils.c ../environment/env_vars.c ../libft/libft.a 
// }