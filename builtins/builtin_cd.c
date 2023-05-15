/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:19:43 by mtravez           #+#    #+#             */
/*   Updated: 2023/05/12 19:23:04 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function takes a String that represents a directory path.
It returns 1 if the directory exists; 0 if it doesn't.
@param dir string with a path to a directory.*/
int	directory_exists(char *dir)
{
	struct stat	status;

	if (!stat(dir, &status) && S_ISDIR(status.st_mode))
		return (1);
	return (0);
}

/*This function replaces the '~' at the beginning of a directory
path with the HOME environmental variable.
@param dir string with a path to a directory.*/
char	*expand_directory(char *dir)
{
	char	*new_dir;

	if (dir && dir[0] == '~')
	{
		new_dir = ft_strjoin_gnl(
				ft_strdup(getenv("HOME")), ft_strdup(&(dir[1])));
		free(dir);
		return (new_dir);
	}
	return (dir);
}

/*This is the built in cd command for minishell.
It takes a directory and changes the current directory to it.
@param dir the directory to change to.*/
int	ft_cd(char *dir)
{
	return (chdir(expand_directory(dir)));
}
