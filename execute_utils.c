/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:36:57 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/30 15:00:48 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_builin_in_pipe(t_exec *exec, t_exec *head)
{
	int	ex;

	ex = 1;
	if (exec->in_fd != -1 || exec->out_fd != -1)
		ex = get_builtin(exec->argv[0])(exec);
	close_all_fd(exec);
	free_hash_list(exec->env);
	free_exec(head);
	exit(ex);
}

int	run_builtin(t_exec *exec)
{
	t_builtin	builtin;

	if (exec->in_fd == -1 || exec->out_fd == -1)
		return (1);
	builtin = get_builtin(exec->argv[0]);
	if (!builtin)
		return (1);
	return (builtin(exec));
}

void	do_parent(t_exec *exec, t_exec *head)
{
	if (!is_builtin(exec->argv[0]))
		execute_command(exec, head);
	else
		run_builin_in_pipe(exec, head);
}

static int	count_cmds(t_exec *exec)
{
	int		i;
	t_exec	*temp;

	i = 0;
	temp = exec;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	wait_please(pid_t parent, t_exec *exec)
{
	int		i;
	pid_t	pid;
	int		status;
	int		error_nr;

	i = count_cmds(exec);
	status = 0;
	error_nr = 0;
	while (i >= 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == parent)
			error_nr = WEXITSTATUS(status);
		i--;
	}
	return (error_nr);
}
