
#include "parser.h"
#include "cmd_builder.h"
#include <stdio.h>
#include <stdbool.h>

int	parse_tokens(t_lexer *lexer, t_cb *cb, t_envar **env)
{
	t_token			*token;
	t_parser_state	state;
	t_redir_type	redir_type;
	int				equal_pos;

	if (!lexer)
	{
		perror("lexer error\n");
		return (EXIT_FAILURE);
	}
	state = VAR_STATE;
	token = lexer->token;
	*cb = cb_init();
	while (token)
	{
		if (state == VAR_STATE)
		{
			if (token->t_type == WORD_TOK || (token->t_type == QUOTE_TOK && is_quotes_close(token->content)))
			{
				if (is_var(token->content, &equal_pos))
				{
					cb_add_var(cb, token->content, equal_pos, env);
					token = token->next_token;
				}
				else
					state = ARGV_STATE;
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				state = REDIR_START_STATE;
				redir_type = get_redir_type(token->t_type);
				if (token->next_token == NULL)
					return (print_syn_error(cb));
				else
					token = token->next_token;
			}
			else if (token->t_type == PIPE_TOK)
			{
				if (!token->next_token || token->next_token->t_type == PIPE_TOK)
					return (print_syn_error(cb));
				else
				{
					token = token->next_token;
					cb_add_cmd_node(cb);
				}
			}
			else
				return (print_syn_error(cb));
		}
		else if (state == ARGV_STATE)
		{
			if (token->t_type == WORD_TOK || (token->t_type == QUOTE_TOK && is_quotes_close(token->content)))
			{
				give_argv_to_cb(cb, token, env);
				state = ARGV_STATE;
			}
			else if (token->t_type == PIPE_TOK)
			{
				if (!token->next_token || token->next_token->t_type == PIPE_TOK)
					return (print_syn_error(cb));
				else
				{
					cb_add_cmd_node(cb);
					state = VAR_STATE;
				}
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				redir_type = get_redir_type(token->t_type);
				state = REDIR_STATE;
				if (token->next_token == NULL)
					return (print_syn_error(cb));
			}
			else
				return (print_syn_error(cb));
			token = token->next_token;
		}
		else if (state == REDIR_STATE)
		{
			if (token->t_type == WORD_TOK || (token->t_type == QUOTE_TOK && is_quotes_close(token->content)))
			{
				give_redir_to_cb(cb, token, env, redir_type);
				state = ARGV_STATE;
			}
			else
				return (print_syn_error(cb));
			token = token->next_token;
		}
		else if (state == REDIR_START_STATE)
		{
			if (token->t_type == WORD_TOK || (token->t_type == QUOTE_TOK && is_quotes_close(token->content)))
			{
				give_redir_to_cb(cb, token, env, redir_type);
				state = VAR_STATE;
			}
			else
				return (print_syn_error(cb));
			token = token->next_token;
		}
		else
			return (print_syn_error(cb));
	}
	return (EXIT_SUCCESS);
}
