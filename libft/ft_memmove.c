/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:32:36 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/17 15:17:42 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function is sympilar to ft_memcpy, but it behaves 
//more cautiously when both pointers overlap, copying the src into dst
//starting at the end
void	*ft_memmove(void *dst, const void *src, int len)
{
	char	*source;
	char	*destiny;
	int		i;

	i = len - 1;
	source = (char *) src;
	destiny = (char *) dst;
	if (dst == 0 && src == 0)
		return (0);
	if (destiny < source || destiny > source + len)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (i >= 0)
		{
			destiny[i] = source[i];
			i--;
		}
	}
	return (dst);
}
