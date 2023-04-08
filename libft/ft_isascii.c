/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:31:22 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/17 15:10:10 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function determines whether the given number
//corresponds to an equivalent character in the ascii table
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
