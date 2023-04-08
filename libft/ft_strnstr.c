/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:01:53 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/27 19:04:59 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This static function exists to needle in haystack only from the 
//pos index
static int	check_word(char *haystack, char *needle, int pos, int len)
{
	int	j;

	j = 0;
	while (needle[j] != '\0' && haystack[j + pos] != '\0')
	{
		j++;
		if (needle[j] == '\0')
			return (pos);
		if (haystack[j + pos] != needle[j] || (j + pos) == len)
			return (-1);
	}
	return (-1);
}

//This function finds a string inside another string
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	int		i;

	i = 0;
	h = (char *) haystack;
	n = (char *) needle;
	if (needle[0] == '\0')
		return (h);
	while ((unsigned int) i < len && h[i] != '\0')
	{
		if (h[i] == n[0])
		{
			if (check_word(h, n, i, len) != -1)
				return (&h[i]);
		}
		i++;
	}
	return (0);
}
