/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:24:29 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/17 15:38:27 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function compares two pointers of each n bytes and returns
//the difference between the first discrepating character
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*temps1;
	unsigned char	*temps2;

	i = 0;
	temps1 = (unsigned char *) s1;
	temps2 = (unsigned char *) s2;
	while ((unsigned int)i < n)
	{
		if (temps1[i] != temps2[i])
			return (temps1[i] - temps2[i]);
		i++;
	}
	return (0);
}
