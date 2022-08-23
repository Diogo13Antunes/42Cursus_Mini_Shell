/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:27:16 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/23 14:46:46 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_alloc_mem	*alloc_mem(void *elem, int type);

void	init_alloc_mem(void)
{
	alloc_mem(0, NO_TYPE);
}

void	save_alloc_mem(void *mem, int type)
{
	alloc_mem(mem, type);
}

void	free_alloc_mem(void)
{
	t_alloc_mem	*mem;

	mem = alloc_mem(0, NO_TYPE);
	if (mem && mem->env)
		free_env_lst(mem->env);
	if (mem && mem->tree)
		free_tree(mem->tree);
	if (mem)
		free(mem);
}

static t_alloc_mem	*alloc_mem(void *elem, int type)
{
	static t_alloc_mem	*mem = 0;

	if (!mem)
	{
		mem = oom_guard2(malloc(sizeof(t_alloc_mem)));
		mem->env = 0;
		mem->tree = 0;
	}
	if (type == TYPE_ENV)
		mem->env = (t_env *) elem;
	else if (type == TYPE_TREE)
		mem->tree = (t_node *) elem;
	return (mem);
}