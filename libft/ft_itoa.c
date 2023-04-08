/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:47:35 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/23 14:47:37 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function counts how many digits are in an integer and returns the 
//value, though it also will return 1 more if the int is negative
static int	ft_count_digits(int n)
{
	int	div;
	int	count;

	count = 0;
	div = n;
	if (n < 0 || div == 0)
		count++;
	while (div != 0)
	{
		div = div / 10;
		count++;
	}
	return (count);
}

//This function returns the positive value of n in an unsigned integer
//and also sets the first parameter of a string to '-' if n is negative
static unsigned int	ft_asign_neg(char *number, int n)
{
	unsigned int	div;

	if (n < 0)
	{
		number[0] = '-';
		div = -n;
	}
	else
		div = n;
	return (div);
}

//This function changes an integer into a string
char	*ft_itoa(int n)
{
	char			*number;
	int				i;
	unsigned int	div;
	int				mod;

	i = ft_count_digits(n);
	number = malloc(sizeof(char) * i + 1);
	if (!number)
		return (NULL);
	div = ft_asign_neg(number, n);
	number[i] = '\0';
	i--;
	if (div == 0)
		number[i] = '0';
	while (div != 0)
	{
		mod = div % 10;
		div = div / 10;
		number[i] = mod + '0';
		i--;
	}
	return (number);
}
