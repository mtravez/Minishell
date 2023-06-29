/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:08:19 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/29 12:08:36 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_put_error_exit(char *error_var, char *error_msg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(error_var, STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			if ((arg[i] == '+' || arg[i] == '-') && i == 0)
			{
				i++;
				continue ;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_overflow(long int nbr, char *str)
{
	if (str[0] == '-' && nbr >= 0)
		return (1);
	if (str[0] != '-' && nbr < 0)
		return (1);
	return (0);
}

int	ft_exit(t_exec *exec)
{
	long int	code;

	code = 0;
	if (exec->argv[1])
	{
		if (exec->argv[2])
			return (ft_put_error_exit(NULL, "too many arguments"));
		code = ms_atoi(exec->argv[1]);
		if (!is_number(exec->argv[1]) || is_overflow(code, exec->argv[1]))
		{
			ft_put_error_exit(exec->argv[1], ": numeric argument required");
			free_hash_list(exec->env);
			free_exec(exec);
			exit(255);
		}
	}
	free_hash_list(exec->env);
	free_exec(exec);
	exit(code);
}
