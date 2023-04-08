/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:55:12 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/28 16:29:34 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

//This function writes in the file fd the given number by using recursion
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	div;

	div = n;
	if (n < 0)
	{
		if (n == INT_MIN)
		{
			ft_putstr_fd("-2147483648", fd);
			return ;
		}
		ft_putchar_fd('-', fd);
		div = -n;
	}
	if (div < 10)
		ft_putchar_fd(div + '0', fd);
	else
	{
		ft_putnbr_fd(div / 10, fd);
		ft_putchar_fd(div % 10 + '0', fd);
	}
}
