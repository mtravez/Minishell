/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:58:53 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/30 16:29:01 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args, int out_fd)
{
	int	i;

	i = 0;
	if (args && args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		i++;
		while (args && args[i])
		{
			ft_putstr_fd(args[i], out_fd);
			if (args[++i])
				ft_putchar_fd(' ', out_fd);
		}
		exit(0);
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], out_fd);
		if (args[++i])
			ft_putchar_fd(' ', out_fd);
	}
	ft_putchar_fd('\n', out_fd);
	exit(0);
}
