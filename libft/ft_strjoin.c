/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:59:14 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/26 20:26:10 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function creates a new string with the joint strings s1 and s2
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint;
	size_t	sizes1;
	size_t	sizes2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	joint = malloc(sizes1 + sizes2 + 1);
	if (!joint)
		return (NULL);
	joint = ft_memcpy(joint, s1, sizes1);
	i = 0;
	while (i < sizes2)
	{
		joint[i + sizes1] = s2[i];
		i++;
	}
	joint[sizes1 + sizes2] = '\0';
	return (joint);
}
