/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:55:27 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/26 20:13:23 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

//This function fills a pointer with n bytes of null using memset
void	ft_bzero(void *s, int n)
{
	ft_memset((void *) s, 0, n);
}
