/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:44:15 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/27 17:16:06 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		if (number * negative <= -922337203685477580 && str[index] > '7')
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
int	ft_atoi(const char *str)
{
	char			*newstr;
	int				negative;
	int				i;
	long int		number;

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
