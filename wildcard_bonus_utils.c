/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:01:15 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/29 17:50:36 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strstrlen(char **strstr)
{
	size_t i;

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
	joint = malloc(sizeof(char *) * (ft_strstrlen(str1) + ft_strstrlen(str2) + 1));
	i = 0;
	while (str1 && str1[i])
	{
		joint[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2 && str2[j])
	{
		joint[i + j] = str2[j];
		j++;
	}
	joint[i + j] = NULL;
	return (joint);
}

// int	main(void)
// {
// 	char	*hi1 = "hello";
// 	char	*hi2 = "helloo";
// 	char	*hi3 = "hellooo";
// 	char	*hi4 = "helloooo";

// 	char	*jn1[] = {hi1, hi2};
// 	char	*jn2[] = {hi3, hi4};
// 	char	**joint = ft_strstrjoin(jn1, jn2);
// 	int	i = 0;
// 	while (joint[i])
// 	{
// 		printf("%s\n", joint[i]);
// 		i++;
// 	}
// 	return (0);
// }