/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:51:49 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/30 13:10:12 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_exec *exec, t_exec *head)
{
	if (exec->in_fd != STDIN_FILENO)
		if (dup2(exec->in_fd, STDIN_FILENO) == -1)
			exit (free_fl(head));
	if (exec->out_fd != STDOUT_FILENO)
		if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
			exit(free_fl(head));
	close_all_fd(exec);
	if (!exec->path)
	{
		if (!ft_strncmp(exec->argv[0], "./", 2) && !access(exec->argv[0], F_OK))
			exit (print_error(exec->argv[0], \
			"Permission denied", 125) + free_fl(head));
		else if (ft_strchr_no_quotes(exec->argv[0], '/'))
			exit(print_error(exec->argv[0], \
			"No such file or directory", 126) + free_fl(head));
		else
			exit(print_error(exec->argv[0], \
			"command not found", 126) + free_fl(head));
	}
	if (is_directory(exec->argv[0]))
		exit (print_error(exec->argv[0], "is a directory", 125) \
		+ free_fl(head));
	if (execve(exec->path, exec->argv, get_environment(exec->env)) == -1)
		exit(1);
	exit(0);
}

void	pipe_exec(t_exec *exec, int	*piped)
{
	int	fd[2];

	if (exec->next && exec->next->token == PIPE_TOK)
	{
		pipe(fd);
		if (exec->out_fd == STDOUT_FILENO)
			exec->out_fd = fd[1];
		else
			close(fd[1]);
		if (exec->next->in_fd == STDIN_FILENO)
			exec->next->in_fd = fd[0];
		else
			(close(fd[0]));
		*piped = 1;
	}
}

int	which_exit(int child_status)
{
	if (g_exit_code != 0)
		return (g_exit_code);
	return (child_status);
}

int	do_exec(t_exec *exec)
{
	t_exec	*temp;
	int		status;
	pid_t	parent;

	temp = exec;
	status = 0;
	signal_handler_fork();
	while (temp)
	{
		pipe_exec(temp, &status);
		if (temp->argv[0])
		{
			if (is_builtin(temp->argv[0]) && !status)
				return (run_builtin(temp));
			else
				parent = fork();
			if (!parent)
				do_parent(temp, exec);
		}
		close_exec_fd(temp);
		temp = temp->next;
	}
	status = wait_please(parent, exec);
	signal_handler_mini();
	return (which_exit(status));
}
