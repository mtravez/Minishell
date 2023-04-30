/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:44:50 by mtravez           #+#    #+#             */
/*   Updated: 2023/02/27 16:18:29 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*This funtion creates a new command type structure with the given parameters
@param cmd the command list for the specifications
@param paths The list of available paths on the environment needed to check for
the command's path in the get_cpath function.*/
t_command	*new_cmd(char **cmd, char **paths)
{
	t_command	*command;

	command = malloc(sizeof(t_command *) + sizeof(char *) * 5);
	if (!command)
		return (NULL);
	command->argv = cmd;
	command->path = get_cpath(paths, cmd[0]);
	return (command);
}

/*This function creates an array of command type structures from the argv in
holder. It assumes that the argc number is at least 5, so it will create the
commands from the 2nd to the penultimate arguments in argv*/
t_command	**get_all_commands(t_holder *holder, char **paths)
{
	int			i;
	int			j;
	t_command	**cmds;

	cmds = malloc(sizeof(t_holder *) * holder->argc - 3);
	j = -1;
	i = 1;
	while (++i <= holder->argc - 2)
		cmds[++j] = new_cmd(ft_split_cmds(holder->argv[i]), paths);
	return (cmds);
}

/*This function initiates a new holder from the given parameters and 
returns NULL if there's a problem*/
t_holder	*init_holder(char **argv, int argc, char **paths)
{
	t_holder	*holder;

	if (argc < 5)
		return (NULL);
	holder = malloc(sizeof(t_holder *) + \
	(sizeof(t_command *) * (argc - 3)) + \
	sizeof(char *) * argc);
	if (!holder)
		return (NULL);
	holder->pipe = new_pipe(argv[1], argv[argc - 1]);
	if (holder->pipe->out_fd == -1)
		return (NULL);
	holder->argc = argc;
	holder->argv = argv;
	holder->cmds = get_all_commands(holder, paths);
	if (!holder->cmds)
		return (NULL);
	return (holder);
}
