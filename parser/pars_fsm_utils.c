
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
	int i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i] != '\0')
	{
		if (str[0] == '\'')
			single_quote++;
		if (str[0] == '"')
			double_quote++;
		if (str[i + 1] == '\0' && str[i] == '\'')
			single_quote++;
		if (str[i + 1] == '\0' && str[i] == '"')
			double_quote++;
		i++;
	}
	if (single_quote == 2 || double_quote == 2)
		return (false);
	return (true);
}
