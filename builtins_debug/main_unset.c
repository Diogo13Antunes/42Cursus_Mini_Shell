/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:31:50 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/02 16:17:26 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	main(int ac, char **av, char **env)
{
	t_env	*enviroment;

	(void)ac;
	(void)av;
	enviroment = get_env_list(env);
	builtin_export(enviroment, NULL);
	builtin_unset(&enviroment, "PATH");
	ft_putstr_fd("\n", STDOUT_FILENO);
	builtin_export(enviroment, NULL);
	return (0);
}
