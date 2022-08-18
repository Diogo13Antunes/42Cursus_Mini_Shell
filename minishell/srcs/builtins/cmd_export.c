/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogoantunes <diogoantunes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:10:13 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/15 12:48:29 by diogoantune      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_identifier_msg(char *identifier)
{
	ft_putstr_fd("export: \'", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_BUILTIN);
}

int	ft_update_elem(t_env *env, char *element)
{
	char	*var;
	int		i;
	t_env	*elem;

	i = find_char(element, '=');
	var = ft_substr(element, 0, i);
	elem = exist_env_elem(env, var);
	if (!elem)
	{
		free(var);
		return (0);
	}
	if (i < 0)
		return (0);
	if (elem->content)
		free(elem->content);
	if (elem->full)
		free(elem->full);
	elem->content = ft_substr(element, i + 1, ft_strlen(element));
	elem->full = create_full_env(elem->variable, elem->content);
	free(var);
	return (1);
}

int	builtin_export(t_env *env, char **elems, int fd)
{
	int		i;
	t_env	*exist;
	int		return_value;

	if (get_matrix_size(elems) == 1)
	{
		print_export(env, fd);
		return (0);
	}
	i = 1;
	return_value = 0;
	while (elems[i])
	{
		if (check_element(elems[i]))
		{
			if (!ft_update_elem(env, elems[i]))
				ft_lstadd_back_env(&env, get_new_env_elem(elems[i]));
		}
		else
			return_value = invalid_identifier_msg(elems[i]);
		i++;
	}
	return (return_value);
}
