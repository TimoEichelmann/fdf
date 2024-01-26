/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:05:19 by teichelm          #+#    #+#             */
/*   Updated: 2023/01/06 15:26:44 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*result;

	if (!lst)
		return (0);
	new_lst = malloc(16);
	result = new_lst;
	while (lst)
	{
		new_lst->content = (*f)(lst->content);
		new_lst->next = malloc(16);
		lst = lst->next;
		if (!new_lst->next)
		{
			ft_lstclear(&result, (*del));
			while (result)
			{
				free (result);
				result = result->next;
			}
		}
		new_lst = new_lst->next;
	}
	return (result);
}
