/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:59:45 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/26 20:20:00 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function creates a new string from the string s from the index start
//and then returns the pointer
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start > size)
		return (ft_strdup(""));
	if (len > size - start)
		len = size - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, &s[start], len);
	sub[len] = '\0';
	return (sub);
}
