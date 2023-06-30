/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_liberate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:44:53 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/30 13:09:20 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_exec_fd(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->in_fd != STDIN_FILENO)
		close(exec->in_fd);
	if (exec->out_fd != STDOUT_FILENO)
		close(exec->out_fd);
}

void	close_all_fd(t_exec *exec)
{
	if (!exec)
		return ;
	close_exec_fd(exec);
	close_all_fd(exec->next);
}

int	free_fl(t_exec *head)
{
	free_hash_list(head->env);
	free_exec(head);
	return (1);
}

int	print_error(char *str, char *details, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (details)
	{
		ft_putstr_fd(details, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		(perror("minishell:"));
	return (exit_code);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
