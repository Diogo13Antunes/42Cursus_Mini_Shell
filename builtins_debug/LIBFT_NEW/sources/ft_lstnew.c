/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:46:18 by dcandeia          #+#    #+#             */
/*   Updated: 2022/05/25 11:43:28 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_env	*ft_lstnew(char *variable, char *content, char *full)
{
	t_env	*link;

	link = (t_env *)malloc(sizeof(t_env));
	if (!link)
		return (NULL);
	link->variable = (char *)variable;
	link->content = (char *)content;
	link->full = (char *)full;
	link->next = NULL;
	return (link);
}
