/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:40:13 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 12:40:13 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_hash_list(t_envar **list)
{
	int	i;

	i = 0;
	while (i < ENVAR_ARRAY_SIZE)
	{
		free_envar(list[i]);
		i++;
	}
	free(list);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_envar	*new_var(char *str, int print)
{
	t_envar	*var;
	char	*data;

	if (!str)
		return (NULL);
	var = malloc(sizeof(t_envar));
	if (!var)
		print_malloc_failed();
	data = ft_strchr(str, '=');
	if (!data)
	{
		free(var);
		return (NULL);
	}
	var->content = ft_strdup(&data[1]);
	var->name = ft_strndup(str, data - str);
	var->print = print;
	var->next = NULL;
	return (var);
}

void	set_env(char **env, t_envar	**envar)
{
	int		i;
	t_envar	*temp;

	i = 0;
	if (env && env[i])
	{
		while (env && env[i])
		{
			temp = new_var(env[i], 1);
			if (!temp)
				return ;
			add_to_array(envar, temp);
			i++;
		}
	}
	else
		add_pwd_to_env(envar);
	add_empty_var("OLDPWD", envar);
	free(get_var(envar, "OLDPWD")->content);
	get_var(envar, "OLDPWD")->content = NULL;
	add_last_exit_status(0, envar);
}
