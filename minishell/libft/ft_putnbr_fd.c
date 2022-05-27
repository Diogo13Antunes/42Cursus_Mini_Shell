/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:33:01 by dsilveri          #+#    #+#             */
/*   Updated: 2021/11/09 12:01:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	char		c;

	if (fd < 0)
		return ;
	nb = (long int)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		ft_putnbr_fd((nb / 10), fd);
	c = nb - ((nb / 10) * 10) + 48;
	write(fd, &c, 1);
}
