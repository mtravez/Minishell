/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:18:46 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/29 21:18:51 by ekulichk         ###   ########.fr       */
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
	char			*str;
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
		while (vars)
		{
			str = str_char_join(
					vars->name, vars->value, '=');
			add_var_to_envar(env, str, node_cmd->flag_is_export);
			free(str);
			vars = vars->next;
		}
		redirs = node_cmd->redirs;
		while (redirs)
		{
			if (redirs->redir_type == IN_REDIR)
			{
				if (node_exec->in_fd != STDIN_FILENO)
				{
					if (!is_closed_fd(close(node_exec->in_fd), redirs->word))
						break ;
				}
				node_exec->in_fd = open(redirs->word, O_RDONLY);
				if (!is_opend_fd(node_exec->in_fd, redirs->word))
					break ;
			}
			else if (redirs->redir_type == OUT_REDIR)
			{
				if (node_exec->out_fd != STDOUT_FILENO)
				{
					if (!is_closed_fd(close(node_exec->out_fd), redirs->word))
						break ;
				}
				node_exec->out_fd = open(redirs->word,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (!is_opend_fd(node_exec->out_fd, redirs->word))
					break ;
			}
			else if (redirs->redir_type == APPEND_REDIR)
			{
				if (node_exec->out_fd != STDOUT_FILENO)
				{
					if (!is_closed_fd(close(node_exec->out_fd), redirs->word))
						break ;
				}
				node_exec->out_fd = open(redirs->word,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (!is_opend_fd(node_exec->out_fd, redirs->word))
					break ;
			}
			else if (redirs->redir_type == HEREDOC_REDIR)
			{
				if (node_exec->in_fd != STDIN_FILENO)
				{
					if (!is_closed_fd(close(node_exec->in_fd), redirs->word))
						break ;
					close(node_exec->in_fd);
				}
				if (!heredoc(redirs->word, redirs->word))
					break ;
				node_exec->in_fd = open("parser/temp.txt", O_RDONLY);
				if (!is_opend_fd(node_exec->in_fd, "parser/temp.txt"))
					break ;
			}
			redirs = redirs->next;
		}
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
