
#include "pars_fsm.h"
#include <stdbool.h>

bool	is_symbolic_tok(t_token_type tok_type)
{
	if (tok_type == PIPE_TOK || tok_type == LESS_TOK || tok_type == DLESS_TOK
		|| tok_type == GREAT_TOK || tok_type == DGREAT_TOK)
		return (true);
	else
		return (false);
}

bool	is_var(char *str, int *equal_pos)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			return (false);
		if (str[i] == '=')
		{
			*equal_pos = i;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_export(char *str)
{
	int			i;
	static char	ex[7] = "export\0";

	i = 0;
	while (str[i] != '\0' && ex[i] != '\0')
	{
		if (str[i] == ex[i])
			if (str[i] != ex[i] || (str[i] == '\0' || ex[i] == '\0'))
				return (false);
		i++;
	}
	return (true);
}

t_redir_type	get_redir_type(t_token_type tok_type)
{
	if (tok_type == LESS_TOK)
		return (IN_REDIR);
	if (tok_type == GREAT_TOK)
		return (OUT_REDIR);
	if (tok_type == DLESS_TOK)
		return (HEREDOC_REDIR);
	if (tok_type == DGREAT_TOK)
		return (APPEND_REDIR);
	return (IN_REDIR);
}

bool	is_quotes_close(char *str)
{
	int				i;
	t_check_quotes	state;

	i = 0;
	state = START;
	while (str[i] != '\0')
	{
		if (state == START)
		{
			if (str[i] == '\'')
				state = SINGLE_OPEN;
			else if (str[i] == '"')
				state = DOUBLE_OPEN;
		}
		else if (state == SINGLE_OPEN)
		{
			if (str[i] == '\'')
				state = SINGLE_CLOSE;
		}
		else if (state == DOUBLE_OPEN)
		{
			if (str[i] == '"')
				state = DOUBLE_CLOSE;
		}
		i++;
	}
	if (state != SINGLE_CLOSE && state != DOUBLE_CLOSE)
		return (false);
	return (true);
}
