/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:33:10 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/01 11:33:50 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	main(int ac, char **av, char **env)
{
	t_env	*enviroment;

	(void)ac;
	(void)av;
	enviroment = get_env_list(env);
	builtin_env(*enviroment, STDOUT_FILENO);
	return (0);
}
