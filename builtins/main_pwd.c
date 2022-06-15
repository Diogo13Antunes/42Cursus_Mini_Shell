/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:35:22 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/01 11:35:35 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	main(void)
{
	int	fd;

	fd = STDOUT_FILENO;
	builtin_pwd(fd);
	fd = open("out.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	builtin_pwd(fd);
	chdir("..");
	builtin_pwd(fd);
	chdir("..");
	builtin_pwd(fd);
	return (0);
}
