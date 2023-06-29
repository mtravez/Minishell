/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:38:57 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/29 18:47:44 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_pwd_to_env(t_envar **env)
{
	char	*str;
	t_envar	*var;

	str = ft_strjoin_gnl(ft_strdup("PWD="), get_pwd());
	var = new_var(str, 1);
	if (!var)
		return ;
	add_to_array(env, var);
	free(str);
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

int	is_var_name_valid(char *name)
{
	size_t	i;

	i = 0;
	if (!name || !name[0])
		return (0);
	if (name[0] == '?' && name[1] == '\0')
		return (1);
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
	return (1);
}

void	add_last_exit_status(int i, t_envar **envar)
{
	t_envar	*var;
	char	*str;

	str = ft_strjoin_gnl(ft_strdup("?="), ft_itoa(i));
	var = new_var(str, 0);
	if (!var)
	{
		printf("failed\n");
		return ;
	}
	add_to_array(envar, var);
	free(str);
}
