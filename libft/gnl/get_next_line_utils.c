/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:41:59 by mtravez           #+#    #+#             */
/*   Updated: 2022/12/08 15:39:08 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//This function creates a new string from the string s from the index start
//and then returns the pointer
char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (!s || start >= ft_strlen(s))
		return (NULL);
	size = ft_strlen(s);
	if (len > size - start)
		len = size - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, &s[start], len);
	sub[len] = '\0';
	return (sub);
}

//This function creates a new string with the joint strings s1 and s2
char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joint;
	size_t	sizes1;
	size_t	sizes2;
	size_t	i;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	joint = malloc(sizes1 + sizes2 + 1);
	if (!joint)
		return (NULL);
	joint = ft_memcpy(joint, s1, sizes1);
	i = 0;
	while (i < sizes2)
	{
		joint[i + sizes1] = s2[i];
		i++;
	}
	joint[sizes1 + sizes2] = '\0';
	free(s1);
	free(s2);
	return (joint);
}
