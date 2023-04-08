/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:19:46 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/17 15:18:31 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function fills a pointer with len bytes of c
void	*ft_memset(void *b, int c, int len)
{
	char	*d;
	int		i;

	d = (char *) b;
	i = 0;
	while (i < len)
	{
		d[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
