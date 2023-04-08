/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:38:55 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/27 19:04:29 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function skips all c characters dirctly after s[index] and returns
//the first index where s[index] is not c. It also returns the same index if
//c is the null character
static int	ft_skip_chars(char const *s, char c, int *index)
{
	if (c == '\0')
		return (*index);
	while (s[*index] == c)
		(*index)++;
	return (*index);
}

//This function skips all non-c characters directly after s[index] and returns
//the first index where s[index] is c or null
static int	ft_skip_non_chars(char const *s, char c, int index)
{
	while (s[index] != c && s[index] != '\0')
		index++;
	return (index);
}

//This function counts how many words are split by c in s and returns
//the number. It also returns 1 if s is not empty and the count is 0 
//(meaning there is not 'c's in the string)
static int	ft_how_many_elements(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			i = ft_skip_non_chars(s, c, i);
		}
		if (s[i] != '\0')
			i++;
	}
	return (count);
}

//This function frees an array and its content and returns null
static void	*ft_freestuff(char **arrarr)
{
	int	i;

	i = 0;
	while (arrarr[i] != 0)
	{
		free(arrarr[i]);
		i++;
	}
	free(arrarr);
	return (NULL);
}

//This function returns an array of strings of the string s that has been
//split by c charaters. It finishes the array with a null pointer
char	**ft_split(char const *s, char c)
{
	char	**arrarr;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	arrarr = malloc((ft_how_many_elements(s, c) + 1) * sizeof(char *));
	if (!arrarr)
		return (NULL);
	i = 0;
	j = ft_skip_chars(s, c, &i);
	k = 0;
	while (s[i] != 0)
	{
		i = ft_skip_non_chars(s, c, i);
		arrarr[k] = ft_substr(s, j, i - j);
		if (arrarr[k++] == NULL)
			return (ft_freestuff(arrarr));
		j = ft_skip_chars(s, c, &i);
		if (k > ft_how_many_elements(s, c) || ft_how_many_elements(s, c) == 1)
			break ;
	}
	arrarr[k] = 0;
	return (arrarr);
}
