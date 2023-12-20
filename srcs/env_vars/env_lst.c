/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:03:31 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/28 14:19:38 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_new_env_elem(char *var, char *cont);
static void		update_shlvl(t_env *shlvl);

t_env	*get_new_env_elem(char *env_str)
{
	t_env	*elem;
	char	*var;
	char	*cont;
	int		i;

	i = get_char_index(env_str, '=');
	if (i > 0)
	{
		var = oom_guard(ft_substr(env_str, 0, i));
		cont = ft_substr(env_str, i + 1, ft_strlen(env_str));
		if (!cont)
		{
			free_str(var);
			oom_guard(NULL);
		}
	}
	else
	{
		var = oom_guard(ft_substr(env_str, 0, ft_strlen(env_str)));
		cont = NULL;
	}
	elem = create_new_env_elem(var, cont);
	return (elem);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*list;

	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		list = *lst;
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

t_env	*get_env_list(char **env)
{
	int		i;
	char	*old_pwd;
	t_env	*list;

	i = 0;
	list = NULL;
	while (env[i])
	{
		ft_lstadd_back_env(&list, get_new_env_elem(env[i]));
		i++;
	}
	if (!exist_env_elem(list, "OLDPWD"))
	{
		old_pwd = oom_guard(ft_calloc(sizeof(char), 7));
		ft_strcat(old_pwd, "OLDPWD");
		ft_lstadd_back_env(&list, create_new_env_elem(old_pwd, 0));
	}
	if (exist_env_elem(list, "SHLVL"))
		update_shlvl(exist_env_elem(list, "SHLVL"));
	return (list);
}

static t_env	*create_new_env_elem(char *var, char *cont)
{
	t_env	*elem;

	elem = oom_guard((t_env *)malloc(sizeof(t_env)));
	elem->variable = var;
	elem->content = cont;
	elem->full = create_full_env(var, cont);
	elem->next = NULL;
	return (elem);
}

static void	update_shlvl(t_env *shlvl)
{
	int		nlevel;

	if (shlvl->content)
	{
		nlevel = ft_atoi(shlvl->content) + 1;
		free(shlvl->content);
	}
	shlvl->content = ft_itoa(nlevel);
	free_str(shlvl->full);
	shlvl->full = create_full_env(shlvl->variable, shlvl->content);
}
