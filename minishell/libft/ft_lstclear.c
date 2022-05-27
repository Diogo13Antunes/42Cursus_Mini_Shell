/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:30:34 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/03 11:30:36 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (!(*lst) || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		del((*lst)->content);
		free((*lst));
		*lst = next;
	}
}
