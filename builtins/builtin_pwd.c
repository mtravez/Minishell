/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:49:00 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/25 14:48:56 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
		return (NULL);
	return (ft_strdup(path));
}

int	ft_pwd(t_exec *exec)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
		return (1);
	ft_putstr_fd(path, exec->out_fd);
	ft_putchar_fd('\n', exec->out_fd);
	return (0);
}
