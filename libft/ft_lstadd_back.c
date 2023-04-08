/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:02:01 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/25 21:44:05 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function adds the new list node to  the back of the
//given list
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (!new)
		return ;
	if (!current)
		*lst = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
