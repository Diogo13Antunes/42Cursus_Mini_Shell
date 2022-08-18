/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:01:51 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/02 12:30:48 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstdelone(t_env *lst)
{
	if (!lst)
		return ;
	if (lst->variable)
		free(lst->variable);
	if (lst->content)
		free(lst->content);
	if (lst->full)
		free(lst->full);
	free(lst);
}
