/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:36:44 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/30 16:53:11 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	able_echo(void)
{
	struct termios	term_settings;

	tcgetattr(STDIN_FILENO, &term_settings);
	term_settings.c_lflag ^= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
}

char	*join_paths(char *path, char *command)
{
	char	*temp;

	temp = ft_strjoin(path, "/");
	temp = ft_strjoin_gnl(temp, ft_strdup(command));
	return (temp);
}

/*This command returns the path to the executable of
whatever function is given as an argument. If the path
doesn't exist, it will return NULL.
@param command The string of the command whose path will
be returned*/
char	*get_path(char *command, t_envar **env)
{
	char	**paths;
	char	*temp;
	int		i;

	if (access(command, X_OK) == 0 && ft_strchr_no_quotes(command, '/'))
		return (ft_strdup(command));
	if (!get_var(env, "PATH") || !get_var(env, "PATH")->content)
		return (NULL);
	temp = get_var(env, "PATH")->content;
	paths = ft_split(temp, ':');
	i = 0;
	while (paths[i])
	{
		temp = join_paths(paths[i], command);
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
