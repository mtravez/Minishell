/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_fsm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:42:25 by ekulichk          #+#    #+#             */
/*   Updated: 2023/05/15 22:36:48 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_FSM_H
# define PARS_FSM_H

# include "minishell.h"

/*
	PIPE_TOK

	TOKEN_TOK
	QUOTE_TOK

	LESS_TOK
	GREAT_TOK
	DLESS_TOK
	DGREAT_TOK
*/
enum e_states
{
	LINE_STATE,
	STR_STATE,
	ARGV_STATE,
	VAR_STATE,
	REDIR_STATE,
	END_STATE,
};

enum e_redir_type
{
	LESS_REDIR,
	GREAT_REDIR,
	DLESS_REDIR,
	DGREAT_REDIRE
};

typedef struct s_redirs_list
{
	enum e_redir_type	redir_type;
	char				*word;
}	t_redirs;

typedef struct s_variables_list
{
	char	*name;
	char	*value;
}	t_vars_list;

typedef char	*t_words_list;

typedef struct s_commands
{
	t_redirs		redirs;
	t_vars_list		vars;
	t_words_list	words;
}	t_cmds;

typedef struct s_commands_list
{
	t_cmds					command;
	struct s_cmd_list		*next;
}	t_cmd_list;

typedef struct s_line
{
	t_cmd_list	cmds;
}	t_line;

void	parse_tokens(t_lexer *lexer);

#endif
