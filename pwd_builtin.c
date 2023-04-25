/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:49:00 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/18 14:30:44 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int out_fd)
{
	char	path[PATH_MAX];
	if (!getcwd(path, sizeof(path)))
		exit(1);
	write(out_fd, path, ft_strlen(path));
	exit(0);
}
