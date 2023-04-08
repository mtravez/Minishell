/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:16:12 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/23 15:37:33 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function prints out the given character in the
//file described by fd
void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
