/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:21:28 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/26 20:30:50 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function uses the del function in the content 
//of every node in lst and frees the node
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next;

	if (!lst)
		return ;
	current = *lst;
	if (!current)
	{
		*lst = NULL;
		return ;
	}
	while (current->next)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	ft_lstdelone(current, del);
	*lst = NULL;
}
