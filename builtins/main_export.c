/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:33:38 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/15 11:17:56 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	main(int ac, char **av, char **env)
{
	t_env	*enviroment;
	char	**elems;
	int		file1;
	int		file2;
	int		file3;

	(void)ac;
	elems = av;
	enviroment = get_env_list(env);
	file1 = open("file1.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	file2 = open("file2.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	file3 = open("file3.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	builtin_export(enviroment, NULL, file1);
	builtin_export(enviroment, elems, STDOUT_FILENO);
	builtin_export(enviroment, NULL, file2);
	builtin_env(*enviroment, file3);
	close(file1);
	close(file2);
	close(file3);
	return (0);
}
