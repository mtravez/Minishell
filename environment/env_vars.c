/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:20:40 by mtravez           #+#    #+#             */
/*   Updated: 2023/05/11 17:39:54 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned long	get_hash_value(char *key)
{
	unsigned long	hash;
	size_t			i;
	size_t			length;

	hash = 0;
	i = 0;
	length = ft_strlen(key);
	while (key[i])
	{
		hash += ((unsigned long *)key)[i];
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
		free(temp->content);
		temp->content = ft_strdup(new_node->content);
		free_envar(new_node);
		return (1);
	}
	return (0);
}

void	add_to_array(t_envar **list, t_envar *node)
{
	unsigned long	hash_nr;
	t_envar			*temp;

	if (!node)
		return ;
	hash_nr = get_hash_value(node->name);
	if (list[hash_nr])
	{
		temp = list[hash_nr];
		while (temp->next)
		{
			if (change_content(temp, node))
				return ;
			temp = temp->next;
		}
		if (change_content(temp, node))
			return ;
		temp->next = node;
	}
	else
		list[hash_nr] = node;
}

t_envar	*new_var(char *str)
{
	t_envar	*var;
	char	*data;

	if (!str)
		return (NULL);
	var = malloc(sizeof(t_envar));
	if (!var)
		return (NULL);
	data = ft_strchr(str, '=');
	if (!data)
	{
		free(var);
		return (NULL);
	}
	var->content = ft_strdup(&data[1]);
	var->name = ft_strndup(str, data - str);
	var->next = NULL;
	return (var);
}

void	print_list(t_envar **list)
{
	size_t	nr;
	t_envar	*temp;

	nr = 0;
	while (nr < ENVAR_ARRAY_SIZE)
	{
		if (list[nr])
		{
			temp = list[nr];
			// printf("[%lu]	", nr);
			while (temp)
			{
				printf("%s=%s\n", temp->name, temp->content);
				temp = temp->next;
			}
			// printf("NULL\n");
		}
		nr++;
	}
}
int	main(int argc, char **argv, char **env)
{
	char	*str = "hello";
	char	*str2 = &str[4];
	t_envar	**list;
	list = ft_calloc(sizeof(t_envar), ENVAR_ARRAY_SIZE);
	
	if (!argc || !argv)
		return (1);
	set_env(env, list);
	print_list(list);
	// t_envar	*hi = new_var("variable=variablebleble");
	// if (list[0])
	// {
	// 	t_envar	*var = list[0];
	// 	if (*var != NULL)
	// 		printf("hello\n");
	// }
	// else
	// {
	// 	list[0] = hi;
	// 	printf("%s\n", list[0]->name);
	// }
	// printf("%lu\n", get_hash_value("PATH") % ENVAR_ARRAY_SIZE);
	// printf("%lu\n", get_hash_value("PWD") % ENVAR_ARRAY_SIZE);
	// printf("%lu\n", get_hash_value("hi") % ENVAR_ARRAY_SIZE);
	// printf("%lu\n", get_hash_value("new") % ENVAR_ARRAY_SIZE);
	// printf("%lu\n", get_hash_value("PATH") % ENVAR_ARRAY_SIZE);
	// printf("%lu\n", get_hash_value("PWD") % ENVAR_ARRAY_SIZE);
	// printf("%lu\n", get_hash_value("HELLO") % ENVAR_ARRAY_SIZE);
}
