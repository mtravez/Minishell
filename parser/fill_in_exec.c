/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:18:46 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 13:26:35 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builder.h"
#include <fcntl.h>
#include <stdbool.h>

t_exec	*fill_in_exec(t_line *line, t_envar **env)
{
	t_fill_in_exec	ex;
	t_exec			*exec;

	exec = NULL;
	fill_in_exec_init(&ex, line);
	while (ex.node_cmd)
	{
		if (ex.node_exec == NULL)
			create_exec(&exec, &ex.node_exec, env);
		else
			create_node(&ex.node_exec, env);
		add_argv_path_to_exec(ex.node_exec, ex.node_cmd, env);
		ex.vars = ex.node_cmd->vars;
		add_var_to_exec(ex.vars, env, ex.node_cmd->flag_is_export);
		ex.redirs = ex.node_cmd->redirs;
		add_redir_to_exec(ex.redirs, ex.node_exec);
		if (!ex.is_pipe_tok)
			pipe_check(&ex);
		else
			ex.node_exec->token = PIPE_TOK;
		ex.node_cmd = ex.node_cmd->next;
	}
	return (exec);
}

void	create_exec(
	t_exec **exec, t_exec **node_exec, t_envar **env)
{
	*node_exec = init_exec(env);
	*exec = *node_exec;
}

void	create_node(t_exec **node_exec, t_envar **env)
{
	(*node_exec)->next = init_exec(env);
	*node_exec = (*node_exec)->next;
}

void	fill_in_exec_init(t_fill_in_exec *ex, t_line *line)
{
	ex->node_exec = NULL;
	ex->node_cmd = line->cmds;
	ex->is_pipe_tok = false;
}

void	pipe_check(t_fill_in_exec *ex)
{
	ex->node_exec->token = WORD_TOK;
	ex->is_pipe_tok = true;
}
