/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:05:54 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/17 15:15:57 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function copies up to n bytes of array src into array dst
void	*ft_memcpy(void *dst, const void *src, int n)
{
	char	*source;
	char	*destiny;
	int		i;

	source = (char *) src;
	destiny = (char *) dst;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		destiny[i] = source[i];
		i++;
	}
	return (dst);
}
