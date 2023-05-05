/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:49:00 by mtravez           #+#    #+#             */
/*   Updated: 2023/05/05 17:42:11 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int out_fd)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
		exit(1);
	ft_putstr_fd(path, out_fd);
	exit(0);
}
