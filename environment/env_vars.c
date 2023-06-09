/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:51:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 17:16:56 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long	get_hash_value(char *key)
{
	unsigned long	hash;
	size_t			i;
	size_t			length;

	hash = 0;
	i = 0;
	length = ft_strlen(key);
	while (i < length)
	{
		hash += (unsigned long)(key[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash % ENVAR_ARRAY_SIZE);
}

int	change_content(t_envar *node, t_envar *new_node)
{
	t_envar	*temp;

	temp = node;
	if (ft_strncmp(new_node->name, temp->name, ft_strlen(new_node->name)) \
	== 0 && ft_strlen(new_node->name) == ft_strlen(temp->name))
	{
		if (temp->content)
			free(temp->content);
		if (new_node->content)
			temp->content = ft_strdup(new_node->content);
		else
			temp->content = NULL;
		free_envar(new_node);
		return (1);
	}
	return (0);
}

t_envar	*get_var(t_envar **env, char *name)
{
	unsigned long	hash_nr;
	t_envar			*temp;

	hash_nr = get_hash_value(name);
	if (env[hash_nr])
	{
		temp = env[hash_nr];
		while (temp)
		{
			if (!ft_strncmp(name, temp->name, ft_strlen(temp->name)))
				return (temp);
			temp = temp->next;
		}
	}
	return (NULL);
}

/*This function will add a variable to the environment list and
return 1 if it succeeded, 0 if it failed. It also checks if the
name of the variable is valid or not.*/
int	add_var_to_envar(t_envar **env, char *str, int print)
{
	t_envar	*new_node;

	new_node = new_var(str, print);
	if (!new_node)
		return (0);
	if (!is_var_name_valid(new_node->name) || \
		!is_quotes_close(new_node->content))
	{
		free_envar(new_node);
		return (0);
	}
	add_to_array(env, new_node);
	return (1);
}

char	**get_environment(t_envar **list)
{
	size_t	nr;
	t_envar	*temp;
	char	**env;

	nr = 0;
	env = NULL;
	while (nr < ENVAR_ARRAY_SIZE)
	{
		if (list[nr])
		{
			temp = list[nr];
			while (temp)
			{
				if (temp->print && temp->content)
					env = ft_strstrjoin(env, to_strstr(ft_strjoin_gnl(\
					ft_strjoin(temp->name, "="), ft_strdup(temp->content))));
				temp = temp->next;
			}
		}
		nr++;
	}
	return (env);
}
