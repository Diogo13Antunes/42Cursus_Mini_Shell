/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:38:02 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/02 15:43:07 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

#define IN_TOP 1
#define IN_MID 2
#define IN_BOT 3

static int	elem_pos(t_env *env, const char *elem)
{
	t_env	*temp;
	int		lst_size;
	int		counter;
	char	*var;

	lst_size = env_lst_size(env);
	counter = 1;
	temp = env;
	while (temp)
	{
		var = temp->variable;
		if (!ft_strcmp(var, elem))
			break ;
		counter++;
		temp = temp->next;
	}
	if (counter == 1)
		return (IN_TOP);
	else if (counter > 1 && counter < lst_size)
		return (IN_MID);
	else if (counter == lst_size)
		return (IN_BOT);
	else
		return (-1);
}

static void	rm_top_env_elem(t_env **env)
{
	t_env	*clean;

	clean = *env;
	*env = (*env)->next;
	ft_lstdelone(clean);
}

static void	rm_mid_bot_env_elem(t_env **env, const char *elem)
{
	t_env	*clean;
	t_env	*temp;

	clean = *env;
	while (clean->next != NULL)
	{
		if (!ft_strcmp(clean->next->variable, elem))
			break ;
		clean = clean->next;
	}
	temp = clean->next;
	clean->next = clean->next->next;
	ft_lstdelone(temp);
}

void	builtin_unset(t_env **env, const char *elem)
{
	int		pos;

	if (!elem || ft_strlen(elem) == 0)
		return ;
	pos = elem_pos(*env, elem);
	if (pos == IN_TOP)
		rm_top_env_elem(env);
	else if (pos == IN_MID)
		rm_mid_bot_env_elem(env, elem);
	else if (pos == IN_BOT)
		rm_mid_bot_env_elem(env, elem);
	else
		return ;
}
