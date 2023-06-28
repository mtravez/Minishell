/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:36:44 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/28 19:45:44 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This command returns the path to the executable of
whatever function is given as an argument. If the path
doesn't exist, it will return NULL.
@param command The string of the command whose path will
be returned*/
char	*get_path(char *command)
{
	char	**paths;
	char	*temp;
	int		i;

	if (access(command, X_OK) == 0 && ft_strchr_no_quotes(command, '/'))
		return (ft_strdup(command));
	temp = getenv("PATH");
	if (!temp)
		return (NULL);
	paths = ft_split(temp, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		temp = ft_strjoin_gnl(temp, ft_strdup(command));
		if (access(temp, X_OK) == 0)
		{
			free_array(paths);
			return (temp);
		}
		free(temp);
		i++;
	}
	free_array(paths);
	return (NULL);
}
