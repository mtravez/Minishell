/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:51:54 by mtravez           #+#    #+#             */
/*   Updated: 2022/12/08 15:39:22 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*This function counts the number of digits that 
will be the result of a conversion ffrom decimal to hexadecimal*/
static int	get_digits_hex(unsigned int n)
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

/*This function uses recursion to print a hexadecimal
@param n unsigned int of the number to be converted to hexadecimal
@param uplo either 'a' or 'A' to know to print in lower- or uppercase*/
static void	ft_print_hex(unsigned int n, char uplo)
{
	if (n >= 16)
	{
		ft_print_hex(n / 16, uplo);
		n = (n % 16);
	}
	if (n > 9)
		ft_putchar_fd(uplo + (n % 10), 1);
	else
		ft_putchar_fd(n + '0', 1);
}

/*This function prints out the conversion from decimal
to hexadecimal and returns the number of digits printed
@param n unsigned int of the number to be converted to hexadecimal
@param uplo either 'a' or 'A' to know to print in lower- or uppercase*/
int	ft_hexprint(unsigned int n, char uplo)
{
	ft_print_hex(n, uplo);
	return (get_digits_hex(n));
}
