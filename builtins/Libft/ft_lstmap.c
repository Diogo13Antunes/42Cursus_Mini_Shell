/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:23:00 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/29 10:41:18 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lista1;
	t_list	*mem;

	if (!lst)
		return (0);
	lista1 = 0;
	while (lst)
	{
		mem = ft_lstnew(f(lst->content));
		if (!mem)
		{
			ft_lstclear(&lista1, del);
			return (0);
		}
		ft_lstadd_back(&lista1, mem);
		lst = lst->next;
	}
	return (lista1);
}
