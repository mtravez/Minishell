/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:47:04 by mtravez           #+#    #+#             */
/*   Updated: 2022/12/08 15:39:34 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*This function returns how many digits the result of
a conversion from decimal to hexadecimal has, but with 
the length off unsigned long long so it will fit wiith pointers*/
static int	get_digits_ptr(unsigned long long n)
{
	int	sum;

	sum = 0;
	while (n)
	{
		n = n / 16;
		sum++;
	}
	if (sum == 0)
		sum++;
	return (sum);
}

/*This function uses recursion to print a hexadecimal.
This time it takes an unsigned long long to acomodate for the size of 
a pointer.
@param n unsigned long long of the number to be converted to hexadecimal*/
static void	ft_print_hex_ptr(unsigned long long n)
{
	if (n >= 16)
	{
		ft_print_hex_ptr(n / 16);
		n = (n % 16);
	}
	if (n > 9)
		ft_putchar_fd('a' + (n % 10), 1);
	else
		ft_putchar_fd(n + '0', 1);
}

/*This function prints out the conversion from unsigned long long
to hexadecimal and returns the number of digits*/
static int	ft_ptr_hex(unsigned long long point)
{
	ft_print_hex_ptr(point);
	return (get_digits_ptr(point));
}

/*This funcion prints out a pointer in he apropiate format and returns
its lenght*/
int	ft_print_ptr(unsigned long long point)
{
	int	count;

	count = 0;
	count += ft_putstr("0x");
	count += ft_ptr_hex(point);
	return (count);
}
