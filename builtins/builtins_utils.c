/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:07:02 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/29 19:37:38 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function determines whether the given character can be
//counted as a white space
static int	is_whitespace(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\n')
		|| (c == '\v') || (c == '\f') || (c == '\r'));
}

//This function turns all digit characters into an integer and returns the 
//result it also checks for the limits and does not allow the integer
// to get pass these
static long int	addnumber(long int number, int negative, char *str, int index)
{
	while (ft_isdigit(str[index]))
	{
		if (number * negative <= -922337203685477580 && str[index] > '8')
			return (0);
		if (number * negative >= 922337203685477580 && str[index] >= '7')
			return (-1);
		number = (number * 10) + (str[index] - '0');
		index++;
	}
	return (number * negative);
}

//This function turns a character array into a number. It ignores
//any white spaces previous to a non-whitespace character and 
//takes the first positive/negative symbol into account for the integer.
long int	ms_atoi(const char *str)
{
	char			*newstr;
	int				negative;
	int				i;
	long long		number;

	newstr = (char *) str;
	number = 0;
	negative = 1;
	i = 0;
	while (is_whitespace(newstr[i]))
		i++;
	if (!ft_isdigit(newstr[i]))
	{
		if (newstr[i] == '-')
			negative *= -1;
		else if (newstr[i] != '+')
			return (0);
		i++;
	}
	return (addnumber(number, negative, newstr, i));
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

t_builtin	get_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (*ft_echo);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (*ft_cd);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (*ft_pwd);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (*ft_env);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (*ft_export);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (*ft_unset);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (*ft_exit);
	return (NULL);
}
