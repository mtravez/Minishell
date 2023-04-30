/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:30:44 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/29 18:57:58 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_holder	*holder;
	char		**paths;
	int			success;

	paths = get_paths(envp);
	holder = init_holder(argv, argc, paths);
	if (!holder)
	{
		ft_putstr_fd("bad holder input", STDERR_FILENO);
		if (paths)
			free_matrix(paths);
		return (1);
	}
	if (paths)
		free_matrix(paths);
	holder->envp = envp;
	success = parent_ultimate(holder);
	return (WEXITSTATUS(success));
}
