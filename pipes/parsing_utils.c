/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:29:49 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/27 14:35:16 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Thiss function returns the first word out of a string, which
in this context is expected to be the command name*/
static char	*get_cmd(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
		if (arg[i++] == ' ')
			break ;
	return (ft_substr(arg, 0, i - 1));
}

/*This function returns a character matrix holding the seprate
instructions for the commands.*/
char	**ft_split_cmds(char *arg)
{
	char	*substr;
	char	**str;
	int		i;
	int		j;

	i = -1;
	while (arg[++i])
		if (arg[i] == 34 || arg[i] == 39)
			break ;
	if (!arg[i])
		return (ft_split(arg, ' '));
	j = (int)(ft_strlen(arg) - 1);
	while (j > i)
		if (arg[j--] == arg[i])
			break ;
	if (j == i)
		return (ft_split(arg, ' '));
	substr = ft_substr(arg, i + 1, j - i);
	str = malloc(sizeof(char *) * 3);
	str[0] = get_cmd(arg);
	str[1] = substr;
	str[2] = NULL;
	return (str);
}
