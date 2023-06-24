#include "../minishell.h"

void	free_single_var(t_envar *var)
{
	if (!var)
		return ;
	free(var->content);
	free(var->name);
	free(var);
}

void	remove_from_envar(t_envar **env, char *name)
{
	unsigned long	hash_nr;
	t_envar			*temp;
	t_envar			*prev;

	hash_nr = get_hash_value(name);
	if (env[hash_nr])
	{
		temp = env[hash_nr];
		prev = temp;
		while (temp)
		{
			if (!ft_strncmp(name, temp->name, ft_strlen(temp->name)))
			{
				if (prev == temp)
					env[hash_nr] = NULL;
				else
					prev->next = temp->next;
				free_single_var(temp);
				temp = NULL;
				return ;
			}
			prev = temp;
			temp = temp->next;
		}
	}
}

int	ft_unset(t_exec *exec)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (exec->argv[i])
	{
		if (!is_var_name_valid(exec->argv[i]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(exec->argv[i], STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			error = 1;
		}
		else
			remove_from_envar(exec->env, exec->argv[i]);
		i++;
	}
	return (error);
}
