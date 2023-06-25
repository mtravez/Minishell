
#include "pars_fsm.h"
#include "cmd_builder.h"
#include <stdio.h>
#include <stdbool.h>

int	parse_tokens(t_lexer *lexer, t_cb *cb, t_envar **env)
{
	t_token			*token;
	t_parser_state	state;
	t_redir_type	redir_type;
	int				equal_pos;
	char			**expanded;
	char			**orig_expanded;

	state = VAR_STATE;
	if (!lexer)
	{
		perror("lexer error\n");
		return (EXIT_FAILURE);
	}
	token = lexer->token;
	if ((lexer->token_nr == 1 && is_symbolic_tok(token->t_type))
		|| lexer->token->t_type == PIPE_TOK)
	{
		print_syn_error();
		return (EXIT_FAILURE);
	}
	*cb = cb_init();
	while (token)
	{
		if (state == VAR_STATE)
		{
			if (token->t_type == WORD_TOK || (token->t_type == QUOTE_TOK && is_quotes_close(token->content)))
			{
				if (is_var(token->content, &equal_pos))
				{
					// ft_printf("var --> var:	%s\n", token->content);
					cb_add_var(cb, token->content, equal_pos, env);
					token = token->next_token;
				}
				else
				{
					// ft_printf("var --> argv:	%s\n", token->content);
					state = ARGV_STATE;
				}
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				// ft_printf("var --> redir_start:	%s\n", token->content);
				state = REDIR_START_STATE;
				redir_type = get_redir_type(token->t_type);
				token = token->next_token;
			}
			else if (token->t_type == PIPE_TOK)
			{
				// ft_printf("var --> var:	%s\n", token->content);
				cb_add_cmd_node(cb);
				token = token->next_token;
			}
			else
			{
				// ft_printf("state var: error\n");
				return (print_syn_error());
			}
		}
		else if (state == ARGV_STATE)
		{
			if (token->t_type == WORD_TOK || (token->t_type == QUOTE_TOK && is_quotes_close(token->content)))
			{
				// ft_printf("argv --> argv:	%s\n", token->content);
				expanded = expand_variables(token->content, env);
				orig_expanded = expanded;
				while (*expanded)
				{
					if (ft_strlen(*expanded) != 0)
						cb_add_argv(cb, *expanded);
					free(*expanded);
					expanded++;
				}
					state = ARGV_STATE;
				free(orig_expanded);
			}
			else if (token->t_type == PIPE_TOK)
			{
				// ft_printf("argv --> var:	%s\n", token->content);
				cb_add_cmd_node(cb);
				state = VAR_STATE;
			}
			else if (token->t_type == LESS_TOK || token->t_type == GREAT_TOK
				|| token->t_type == DLESS_TOK || token->t_type == DGREAT_TOK)
			{
				// ft_printf("argv --> redir:	%s\n", token->content);
				redir_type = get_redir_type(token->t_type);
				state = REDIR_STATE;
			}
			else
			{
				// ft_printf("state argv: error\n");
				return (print_syn_error());
			}
			token = token->next_token;
		}
		else if (state == REDIR_STATE)
		{
			if (token->t_type == WORD_TOK || (token->t_type == QUOTE_TOK && is_quotes_close(token->content)))
			{
				// ft_printf("redir --> argv:	%s\n", token->content);
				if (redir_type == HEREDOC_REDIR && token->t_type == QUOTE_TOK)
					cb_add_redir(cb, remove_quotes(token->content), redir_type, env);
				else
					cb_add_redir(cb, token->content, redir_type, env);
				// printf("type %d, content %s\n", token->t_type, token->content);
				state = ARGV_STATE;
			}
			else
			{
				// ft_printf("state redir: error\n");
				return (print_syn_error());
			}
			token = token->next_token;
		}
		else if (state == REDIR_START_STATE)
		{
			if (token->t_type == WORD_TOK || (token->t_type == QUOTE_TOK && is_quotes_close(token->content)))
			{
				// ft_printf("redir_start --> var:	%s\n", token->content);
				// ft_printf("redir --> argv:	%s\n", token->content);
				if (redir_type == HEREDOC_REDIR && token->t_type == QUOTE_TOK)
					cb_add_redir(cb, remove_quotes(ft_strdup(token->content)), redir_type, env);
				else
					cb_add_redir(cb, token->content, redir_type, env);
				// printf("type %d, content %s\n", token->t_type, token->content);
				state = VAR_STATE;
			}
			else
			{
				// ft_printf("state redir_start: error\n");
				return (print_syn_error());
			}
			token = token->next_token;
		}
		else
			return (print_syn_error());
	}
	return (0);
}

int	print_syn_error(void)
{
	printf("syntax error\n");
	return (EXIT_FAILURE);
}
