
#include "pars_fsm.h"
#include <stdbool.h>
#include <stdlib.h>

bool	is_symbolic_tok(t_token_type tok_type)
{
	if (tok_type == PIPE_TOK)
		ft_printf("syntax error near unexpected token `|'\n");
	else if (tok_type == LESS_TOK || tok_type == DLESS_TOK
		|| tok_type == GREAT_TOK || tok_type == DGREAT_TOK)
		ft_printf("syntax error near unexpected token `newline'\n");
	else
		return (false);
	return (true);
}

// return equal position
// check if only one quote
// count len for var_name and for value
bool	is_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}
