#include "../minishell.h"

int	print_export(t_envar **list, int fd)
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
					if (temp->content)
					{
						ft_putstr_fd("=\"", fd);
						ft_putstr_fd(temp->content, fd);
						ft_putchar_fd('\"', fd);
					}
					ft_putchar_fd('\n', fd);
				}
				temp = temp->next;
			}
		}
		nr++;
	}
	return (0);
}

int	print_identifier_error(char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	return (1);
}

void	add_empty_var(char *var, t_envar **env)
{
	t_envar	*envar;

	envar = new_var(var, 1);
	if (envar)
	{
		free(envar->content);
		envar->content = NULL;
		add_to_array(env, envar);
	}
	free(var);
}

int	ft_export(t_exec *exec)
{
	t_envar	*node;
	int		error;
	int		i;

	node = NULL;
	error = 0;
	i = 1;
	if (!exec->argv[1])
		return (print_export(exec->env, exec->out_fd));
	while (exec->argv[i])
	{
		if (ft_strchr_no_quotes(exec->argv[i], '='))
		{
			if (!add_var_to_envar(exec->env, exec->argv[i], 1))
				error = print_identifier_error(exec->argv[i]);
		}
		else if (!is_var_name_valid(exec->argv[i]))
			error = print_identifier_error(exec->argv[i]);
		else
		{
			node = get_var(exec->env, exec->argv[i]);
			if (!node)
				add_empty_var(ft_strjoin(exec->argv[i], "="), exec->env);
			else
				node->print = 1;
		}
		i++;
	}
	return (error);
}
