/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:11:22 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/26 20:27:58 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function returns a string where every character has been passed
//through the f function that`s been given as a parameter
//The f function takes the index of the given character from string s
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = malloc((ft_strlen(s) * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	while (i < ft_strlen(s))
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
