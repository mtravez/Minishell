/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:59:08 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/22 16:51:05 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function concatenates the src string into the end of the dst string
//and returns the final size of dst
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < dstsize && dst[i] != '\0')
		i++;
	if (i == dstsize)
		return (i + ft_strlen(src));
	k = i;
	while (src[j] != 0)
	{
		if (i < dstsize - 1)
		{
			dst[k] = src[j];
			k++;
		}
		i++;
		j++;
	}
	dst[k] = '\0';
	return (i);
}
