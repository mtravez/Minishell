/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:18:46 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 01:29:09 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builder.h"
#include <fcntl.h>
#include <stdbool.h>

t_exec	*fill_in_exec(t_line *line, t_envar **env)
{
	t_exec			*exec;
	t_exec			*node_exec;
	t_cmd_list		*node_cmd;
	t_var_list		*vars;
	t_redir_list	*redirs;
	char			**argv;
	bool			is_pipe_tok;

	node_exec = NULL;
	node_cmd = line->cmds;
	is_pipe_tok = false;
	while (node_cmd)
	{
		if (node_exec == NULL)
		{
			node_exec = init_exec(env);
			exec = node_exec;
		}
		else
		{
			node_exec->next = init_exec(env);
			node_exec = node_exec->next;
		}
		move_argv(&node_exec->argv, &node_cmd->argv);
		argv = node_exec->argv;
		if (argv[0])
			node_exec->path = get_path(argv[0], env);
		vars = node_cmd->vars;
		add_var_to_exec(vars, env, node_cmd->flag_is_export);
		redirs = node_cmd->redirs;
		add_redir_to_exec(redirs, node_exec);
		if (!is_pipe_tok)
		{
			node_exec->token = WORD_TOK;
			is_pipe_tok = true;
		}
		else
			node_exec->token = PIPE_TOK;
		node_cmd = node_cmd->next;
	}
	return (exec);
}
