#include "../minishell.h"

void	free_envar(t_envar *var)
{
	if (!var)
		return ;
	free(var->name);
	free(var->content);
	free_envar(var->next);
	free(var);
}

int	is_var_name_valid(char *name)
{
	size_t	i;

	i = 0;
	while (name && name[i])
	{
		if (!(name[i] == '_' || ft_isalnum(name[i])))
			return (0);
		i++;
	}
	i = 0;
	while (name && name[i] && ft_isdigit(name[i]))
		i++;
	if (i)
		return (0);
}