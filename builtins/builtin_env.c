/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:48:33 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/27 15:53:22 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_envar **list, int fd)
{
	size_t	nr;
	t_envar	*temp;

	nr = 0;
	while (nr < ENVAR_ARRAY_SIZE)
	{
		if (list[nr])
		{
			temp = list[nr];
			while (temp)
			{
				if (temp->print && temp->content)
				{
					ft_putstr_fd(temp->name, fd);
					ft_putchar_fd('=', fd);
					ft_putstr_fd(temp->content, fd);
					ft_putchar_fd('\n', fd);
				}
				temp = temp->next;
			}
		}
		nr++;
	}
}

int	ft_env(t_exec *exec)
{
	print_list(exec->env, exec->out_fd);
	return (1);
}
