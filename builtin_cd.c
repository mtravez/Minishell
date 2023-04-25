/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:31:07 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/19 16:24:06 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	directory_exists(char *dir)
{
	struct stat status;
	
	if (!stat(dir, &status) && S_ISDIR(status.st_mode))
		return (1);
	return (0);
}

char	*expand_directory(char *dir)
{
	char	*new_dir;

	if (dir && dir[0] == '~')
	{
		new_dir = ft_strjoin_gnl(ft_strdup(getenv("HOME")), ft_strdup(&(dir[1])));
		free(dir);
		return (new_dir);
	}
	return (dir);
}

int	cd(char *dir)
{
	exit(chdir(dir));
}
