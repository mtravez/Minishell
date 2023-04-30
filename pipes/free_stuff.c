/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:44:50 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/27 14:00:49 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*This function frees a character matrix*/
void	free_matrix(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

/*This function frees a command type structure*/
void	free_cmd(t_command *command)
{
	free(command->path);
	free_matrix(command->argv);
	free(command);
}

/*This unction frees a holder type structure*/
void	free_holder(t_holder *holder)
{
	int	i;

	i = 0;
	if (holder->cmds)
	{
		while (holder->cmds[i])
			free_cmd(holder->cmds[i++]);
	}
	free(holder->cmds);
	close (holder->pipe->in_fd);
	close (holder->pipe->out_fd);
	free(holder->pipe);
	holder->argv = NULL;
	holder->envp = NULL;
	free(holder);
}
