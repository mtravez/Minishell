/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:19:43 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/30 13:55:38 by mtravez          ###   ########.fr       */
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
char	*expand_directory(char *dir, t_envar **env)
{
	char	*new_dir;
	char	*home_str;
	t_envar	*home;

	home = get_var(env, "HOME");
	home_str = ft_strdup(".");
	if (home && home->content)
	{
		free(home_str);
		home_str = ft_strdup(home->content);
	}
	if (dir && dir[0] == '~')
	{
		new_dir = ft_strjoin_gnl(home_str, ft_strdup(&(dir[1])));
		return (new_dir);
	}
	if (!dir)
		return (home_str);
	free(home_str);
	return (ft_strdup(dir));
}

char	*get_expanded_dir(char *arg, t_envar **env)
{
	char	*dir;

	dir = expand_directory(arg, env);
	if (ft_strncmp(dir, "", 1) == 0)
	{
		free(dir);
		dir = ft_strdup(".");
	}
	return (dir);
}

/*This is the built in cd command for minishell.
It takes a directory and changes the current directory to it.
@param dir the directory to change to.*/
int	ft_cd(t_exec *exec)
{
	int		exit_nr;
	char	*dir;

	dir = get_expanded_dir(exec->argv[1], exec->env);
	if (access(dir, F_OK) != 0)
	{
		ft_putstr_fd("minishell: cd: ", exec->out_fd);
		perror(dir);
		free(dir);
		return (1);
	}
	exit_nr = chdir(dir);
	free(dir);
	if (exit_nr == -1)
		return (1);
	dir = ft_strjoin("OLDPWD=", get_var(exec->env, "PWD")->content);
	add_var_to_envar(exec->env, dir, 1);
	free(dir);
	dir = ft_strjoin_gnl(ft_strdup("PWD="), get_pwd());
	free(dir);
	add_var_to_envar(exec->env, dir, 1);
	return (0);
}
