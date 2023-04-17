/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:55:27 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/17 12:08:05 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//This function fills a pointer with n bytes of null using memset
void	ft_bzero(void *s, int n)
{
	ft_memset((void *) s, 0, n);
}
