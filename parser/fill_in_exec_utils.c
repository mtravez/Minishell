/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:15:32 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 16:57:05 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builder.h"
#include <fcntl.h>
#include <stdbool.h>

t_exec	*init_exec(t_envar **env)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (exec == NULL)
		print_malloc_failed();
	exec->argv = malloc(sizeof(char *));
	if (exec->argv == NULL)
		print_malloc_failed();
	exec->argv[0] = NULL;
	exec->env = env;
	exec->path = NULL;
	exec->in_fd = STDIN_FILENO;
	exec->out_fd = STDOUT_FILENO;
	exec->token = 0;
	exec->next = NULL;
	return (exec);
}

void	move_argv(t_argv *dst, t_argv *src)
{
	free_array(*dst);
	*dst = *src;
	*src = NULL;
}

bool	is_opend_fd(int fd, char *file_name)
{
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file_name);
		return (false);
	}
	return (true);
}

bool	is_closed_fd(int is_close, char *file_name)
{
	if (is_close != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file_name);
		return (false);
	}
	return (true);
}

bool	heredoc(char *delimiter, char *file_name)
{
	int		fd;
	char	*line;

	(void)file_name;
	fd = open("parser/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!is_opend_fd(fd, "parser/temp.txt"))
		return (false);
	line = readline("> ");
	while (line && ft_strncmp(
			line, delimiter, ft_strlen(delimiter) + 1) != 0)
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
	}
	if (!is_closed_fd(close(fd), file_name))
	{
		free(line);
		return (false);
	}
	free(line);
	return (true);
}
