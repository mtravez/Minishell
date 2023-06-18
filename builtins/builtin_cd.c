/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:19:43 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/18 16:50:03 by mtravez          ###   ########.fr       */
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
	if (!dir)
		return (ft_strdup(getenv("HOME")));
	return (ft_strdup(dir));
}

/*This is the built in cd command for minishell.
It takes a directory and changes the current directory to it.
@param dir the directory to change to.*/
int	ft_cd(t_exec *exec)
{
	int		exit_nr;
	char	*dir;

	dir = expand_directory(exec->argv[1]);
	if (access(dir, F_OK) != 0)
	{
		perror("minishell: ");
		return (1);
	}
	exit_nr = chdir(dir);
	if (exit_nr == -1)
		return (1);
	add_var_to_envar(exec->env, ft_strjoin("OLDPWD=", get_var(exec->env, "PWD")->content), 1);
	add_var_to_envar(exec->env, ft_strjoin_gnl(ft_strdup("PWD="), get_pwd()), 1);
	return (0);
}
