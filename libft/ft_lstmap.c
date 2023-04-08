/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:58:56 by mtravez           #+#    #+#             */
/*   Updated: 2022/10/26 12:57:22 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function iterates the function f in the content of every node 
//in the list creating a new list with the modified contents. It uses
//del to delete the nodes when necessary
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new;
	t_list	*head;

	if (!lst || !del || !f)
		return (NULL);
	current = ft_lstnew(f(lst->content));
	if (!current)
		return (NULL);
	head = current;
	while (lst->next)
	{
		lst = lst->next;
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		current->next = new;
		current = current->next;
	}
	return (head);
}
