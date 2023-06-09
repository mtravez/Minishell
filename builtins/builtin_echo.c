/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:58:53 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/25 14:48:16 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n_flag(char *arg)
{
	int	i;

	if (!(arg && !ft_strncmp(arg, "-n", 2)))
		return (0);
	i = 1;
	while (arg && arg[i])
		if (arg[i++] != 'n')
			return (0);
	return (1);
}

/*This command takes an array of arguments and writes them out in
the given argument out_fd followed by a new line. It can take the
option "-n" so the new line will be suppressed.*/
int	ft_echo(t_exec *exec)
{
	int	i;

	i = 1;
	if (exec->out_fd == -1)
		return (1);
	if (exec->argv && exec->argv[i] && is_n_flag(exec->argv[i]))
	{
		while (is_n_flag(exec->argv[i]))
			i++;
		while (exec->argv && exec->argv[i])
		{
			ft_putstr_fd(exec->argv[i], exec->out_fd);
			if (exec->argv[++i])
				ft_putchar_fd(' ', exec->out_fd);
		}
		return (0);
	}
	while (exec->argv && exec->argv[i])
	{
		ft_putstr_fd(exec->argv[i], exec->out_fd);
		if (exec->argv[++i])
			ft_putchar_fd(' ', exec->out_fd);
	}
	ft_putchar_fd('\n', exec->out_fd);
	return (0);
}
