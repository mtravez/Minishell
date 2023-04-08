/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:26:38 by mtravez           #+#    #+#             */
/*   Updated: 2022/12/08 15:39:28 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*This function reurns how many digits there are 
in an int*/
static int	get_digits(int n)
{
	int	sum;

	sum = 0;
	while (n)
	{
		n = n / 10;
		sum++;
	}
	if (sum == 0)
		sum++;
	return (sum);
}

/*This function prints a string and returns the number
of characters inside. If the sttring is null, it will run
itself with the string "(null)" instead*/
int	ft_putstr(char *string)
{
	if (!string)
	{
		return (ft_putstr("(null)"));
	}
	ft_putstr_fd(string, 1);
	return (ft_strlen(string));
}

/*This function prints a character and returns 1*/
int	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

/*This function prints a number and returns how many digits
it has*/
int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	ft_putnbr_fd(n, 1);
	if (n < 0)
		count++;
	count += get_digits(n);
	return (count);
}

/*This function prints out an unsigned int and returns
how many digits it has*/
int	ft_put_unsigned(unsigned int n)
{
	unsigned int	div;
	int				count;

	count = 0;
	div = n;
	if (div < 10)
		count += ft_putchar(div + '0');
	else
	{
		count += ft_put_unsigned(div / 10);
		count += ft_putchar(div % 10 + '0');
	}
	return (count);
}
