/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:44:10 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/01 15:01:10 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*This function is the child process for ultimate parent.
Here the linux commands are executed in pipes and, depending on the index, 
printed out on the output file.
@param holder the holder containing the arguments for the commands 
and file descriptors
@param index the index of the command to be executed
@param pipes the pipe created in the parent for */
static int	child(t_holder *holder, int index, int *pipes)
{
	if (dup2(holder->pipe->in_fd, STDIN_FILENO) == -1)
		exit(1);
	if (index != holder->argc - 4)
	{
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	else if (dup2(holder->pipe->out_fd, STDOUT_FILENO) == -1)
		exit(1);
	close (pipes[1]);
	close (holder->pipe->in_fd);
	close (holder->pipe->out_fd);
	close (pipes[0]);
	if (!holder->cmds[index]->path)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(holder->cmds[index]->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (execve(holder->cmds[index]->path, \
	holder->cmds[index]->argv, holder->envp) == -1)
		exit(1);
	exit(0);
}

/*This function closes all necessary file descriptors after the execution of
the child*/
static void	close_parent(t_holder *holder, int index, int *fd)
{
	close (holder->pipe->in_fd);
	holder->pipe->in_fd = fd[0];
	close (fd[1]);
	if (index == holder->argc - 4)
	{
		close (fd[0]);
		close (holder->pipe->out_fd);
	}
}

/*This function executes all commands in holder using pipes. If there
is an error, it will return the error status.*/
int	parent_ultimate(t_holder *holder)
{
	int	her;
	int	fd[2];
	int	status;
	int	index;

	index = 0;
	status = 0;
	while (index < holder->argc - 3)
	{
		if (pipe(fd))
			return (0);
		her = fork();
		if (her == 0)
			child(holder, index, fd);
		else
			close_parent(holder, index++, fd);
	}
	waitpid(her, &status, 0);
	return (status);
}
