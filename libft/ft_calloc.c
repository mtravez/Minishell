/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:08:55 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/27 15:23:49 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

//This function allocates enough space for count number of
//objects of each size bytes of memory. It then fills the bytes 
//with zero and returns a pointer to the allocated memory.
void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;

	i = count * size;
	if (size && count != (i / size))
		return (NULL);
	mem = malloc(size * count);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}
