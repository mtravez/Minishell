/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:01:09 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 02:02:21 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builder.h"
#include <fcntl.h>

void	add_var_to_exec(
	t_var_list *vars, t_envar **env, int is_export)
{
	char	*str;

	while (vars)
	{
		str = str_char_join(
				vars->name, vars->value, '=');
		add_var_to_envar(env, str, is_export);
		free(str);
		vars = vars->next;
	}
}

bool	out_redir(t_redir_list *redirs, t_exec *node_exec)
{
	if (node_exec->out_fd != STDOUT_FILENO)
	{
		if (!is_closed_fd(close(node_exec->out_fd), redirs->word))
			return (false);
	}
	if (redirs->redir_type == OUT_REDIR)
		node_exec->out_fd = open(
				redirs->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirs->redir_type == APPEND_REDIR)
		node_exec->out_fd = open(
				redirs->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!is_opend_fd(node_exec->out_fd, redirs->word))
		return (false);
	return (true);
}

bool	heredoc_redir(t_redir_list *redirs, t_exec *node_exec)
{
	if (node_exec->in_fd != STDIN_FILENO)
	{
		if (!is_closed_fd(close(node_exec->in_fd), redirs->word))
			return (false);
		close(node_exec->in_fd);
	}
	if (!heredoc(redirs->word, redirs->word))
		return (false);
	node_exec->in_fd = open("parser/temp.txt", O_RDONLY);
	if (!is_opend_fd(node_exec->in_fd, "parser/temp.txt"))
		return (false);
	return (true);
}

void	add_redir_to_exec(t_redir_list *redirs, t_exec *node_exec)
{
	while (redirs)
	{
		if (redirs->redir_type == IN_REDIR)
		{
			if (node_exec->in_fd != STDIN_FILENO)
				if (!is_closed_fd(close(node_exec->in_fd), redirs->word))
					break ;
			node_exec->in_fd = open(redirs->word, O_RDONLY);
			if (!is_opend_fd(node_exec->in_fd, redirs->word))
				break ;
		}
		else if (redirs->redir_type == OUT_REDIR
			|| redirs->redir_type == APPEND_REDIR)
		{
			if (!out_redir(redirs, node_exec))
				break ;
		}
		else if (redirs->redir_type == HEREDOC_REDIR)
		{
			if (!heredoc_redir(redirs, node_exec))
				break ;
		}
		redirs = redirs->next;
	}
}
