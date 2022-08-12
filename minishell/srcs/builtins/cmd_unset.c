/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:38:02 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/12 15:31:56 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define IN_TOP 1
#define IN_MID 2
#define IN_BOT 3

void	ft_lstdelenv(t_env *lst)
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
	ft_lstdelenv(clean);
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
	ft_lstdelenv(temp);
}

void	builtin_unset(t_env **env, char **elems)
{
	int		pos;
	int		i;

	i = 1;
	while (elems[i])
	{
		if (!elems[i] || ft_strlen(elems[i]) == 0)
			return ;
		pos = elem_pos(*env, elems[i]);
		if (pos == IN_TOP)
			rm_top_env_elem(env);
		else if (pos == IN_MID)
			rm_mid_bot_env_elem(env, elems[i]);
		else if (pos == IN_BOT)
			rm_mid_bot_env_elem(env, elems[i]);
		i++;
	}
}
