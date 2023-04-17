/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:51:31 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/17 12:10:53 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*This function checks the character after the '%' and executes the
appropiate conversions. It also returns the number of characters printed
as a result*/
static int	ft_print_vars(char *string, va_list params)
{
	if (string[1] == 'c')
		return (ft_putchar(va_arg(params, int)));
	else if (string[1] == 's')
		return (ft_putstr(va_arg(params, char *)));
	else if (string[1] == 'x')
		return (ft_hexprint((unsigned int)va_arg(params, int), 'a'));
	else if (string[1] == 'X')
		return (ft_hexprint((unsigned int)va_arg(params, int), 'A'));
	else if (string[1] == 'i')
		return (ft_putnbr(va_arg(params, int)));
	else if (string[1] == 'd')
		return (ft_putnbr(va_arg(params, int)));
	else if (string[1] == 'u')
		return (ft_put_unsigned(va_arg(params, unsigned int)));
	else if (string[1] == 'p')
		return (ft_print_ptr(va_arg(params, unsigned long long)));
	else if (string[1] == '%')
		return (ft_putchar('%'));
	return (0);
}

/*This function prints out strings and whatever variables you want.
It also returns the amount of characters it has printed.*/
int	ft_printf(const char *string, ...)
{
	int		index;
	int		count;
	va_list	ap;

	index = 0;
	count = 0;
	if (!string)
		return (0);
	va_start(ap, string);
	while (string[index])
	{
		if (string[index] == '%')
		{
			count += ft_print_vars((char *)&(string[index]), ap);
			index++;
		}
		else
		count += ft_putchar(string[index]);
		index++;
	}
	return (count);
}
