/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:50:15 by dcandeia          #+#    #+#             */
/*   Updated: 2022/05/23 16:14:19 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd;

	(void)ac;
	(void)av;
	i = 0;
	fd = open("in_file.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	while (env[i])
	{
		ft_putstr_fd(env[i], fd);
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	return (0);
}
