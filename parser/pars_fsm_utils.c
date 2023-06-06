
#include "pars_fsm.h"
#include <stdbool.h>
#include <stdlib.h>

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

t_redir_type	get_redir_type(t_token_type tok_type)
{
	if (tok_type == LESS_TOK)
		return (LESS_REDIR);
	if (tok_type == GREAT_TOK)
		return (GREAT_REDIR);
	if (tok_type == DLESS_TOK)
		return (DLESS_REDIR);
	if (tok_type == DGREAT_TOK)
		return (DGREAT_REDIR);
	return (LESS_REDIR);
}

char	*str_space_join(char const *s1, char const *s2)
{
	char	*joint;
	size_t	sizes1;
	size_t	sizes2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	joint = malloc(sizes1 + sizes2 + 2);
	if (!joint)
		return (NULL);
	ft_memcpy(joint, s1, sizes1);
	joint[sizes1] = ' ';
	ft_memcpy(joint + sizes1 + 1, s2, sizes2);
	joint[sizes1 + sizes2 + 1] = '\0';
	return (joint);
}
