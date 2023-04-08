/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:21:16 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/17 15:07:48 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function determines whether the given character is
//a digit or a letter
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
