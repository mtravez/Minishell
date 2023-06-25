#include "../minishell.h"

void	print_export(t_envar **list, int fd)
{
	size_t	nr;
	t_envar	*temp;

	nr = 0;
	while (nr < ENVAR_ARRAY_SIZE)
	{
		if (list[nr])
		{
			temp = list[nr];
			while (temp)
			{
				if (temp->print)
				{
					ft_putstr_fd("declare -x ", fd);
					ft_putstr_fd(temp->name, fd);
					ft_putstr_fd("=\"", fd);
					ft_putstr_fd(temp->content, fd);
					ft_putstr_fd("\"\n", fd);
				}
				temp = temp->next;
			}
		}
		nr++;
	}
}

int	ft_export(t_exec *exec)
{
	t_envar	*node;
	int	error;
	int	i;

	node = NULL;
	error = 0;
	i = 1;
	if (!exec->argv[1])
	{
		print_export(exec->env, exec->out_fd);
		return (0);
	}
	while (exec->argv[i])
	{
		if (ft_strchr_no_quotes(exec->argv[i], '='))
			add_var_to_envar(exec->env, exec->argv[1], 1);
		else if (!is_var_name_valid(exec->argv[i]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(exec->argv[i], STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			error = 1;
		}
		else
		{
			node = get_var(exec->env, exec->argv[1]);
			if (!node)
				return (0);
			node->print = 1;
		}
		i++;
	}
	return (error);
}