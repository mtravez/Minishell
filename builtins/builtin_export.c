/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:08:46 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/29 12:40:50 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_str_var(t_envar *var, int fd)
{
	if (var->print)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(var->name, fd);
		if (var->content)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(var->content, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
	}
}

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
				put_str_var(temp, fd);
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

void	add_empty_var(char *name, t_envar **env)
{
	t_envar	*envar;
	char	*str;

	envar = get_var(env, name);
	if (!envar)
	{
		str = ft_strjoin(name, "=");
		envar = new_var(str, 1);
		if (envar)
		{
			free(envar->content);
			envar->content = NULL;
			add_to_array(env, envar);
		}
		free(str);
	}
	else
		envar->print = 1;
}

int	ft_export(t_exec *exec)
{
	t_envar	*node;
	int		error;
	int		i;

	node = NULL;
	error = 0;
	i = 0;
	if (!exec->argv[1])
		return (print_export(exec->env, exec->out_fd));
	while (exec->argv[++i])
	{
		if (ft_strchr_no_quotes(exec->argv[i], '='))
		{
			if (!add_var_to_envar(exec->env, exec->argv[i], 1))
				error = print_identifier_error(exec->argv[i]);
		}
		else if (!is_var_name_valid(exec->argv[i]))
			error = print_identifier_error(exec->argv[i]);
		else
			add_empty_var(exec->argv[i], exec->env);
	}
	return (error);
}
