/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_matrix_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:21:31 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/06 12:33:22 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	print_env_matrix(char **matrix, int fd)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	ft_putstr_fd("\n", fd);
	return ;
}

int	main(int ac, char **av, char **env)
{
	t_env	*enviroment;
	char	**matrix_env;

	(void)ac;
	(void)av;
	enviroment = get_env_list(env);
	builtin_env(*enviroment, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	matrix_env = get_env_matrix(enviroment);
	print_env_matrix(matrix_env, STDOUT_FILENO);
	return (0);
}
