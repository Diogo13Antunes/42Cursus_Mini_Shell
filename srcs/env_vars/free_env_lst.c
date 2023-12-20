/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:55:48 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/28 11:56:20 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_lst(t_env	*env)
{
	t_env	*next;

	if (!env)
		return ;
	while (env)
	{
		next = env->next;
		free_str(env->variable);
		free_str(env->content);
		free_str(env->full);
		free(env);
		env = next;
	}
}
