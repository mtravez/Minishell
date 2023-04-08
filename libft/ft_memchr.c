/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:10:48 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/26 19:38:25 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function searches within the first n bytes of s
//for the first occurrance of c and returns the pointer to it
void	*ft_memchr(const void *s, int c, size_t n)
{
	int					i;
	const unsigned char	*temp;

	i = 0;
	temp = (const unsigned char *) s;
	while ((size_t)i < n)
	{
		if (temp[i] == (unsigned char)c)
			return ((void *)&temp[i]);
		i++;
	}
	return (0);
}
