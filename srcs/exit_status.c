/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:48:55 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/28 18:24:05 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define OP_SET_CODE     1
#define OP_GET_CODE     2
#define OP_CLEAR_CODE	3

static int	exit_status_controler(int exit_status, int op);

void	set_exit_status(int exit_status)
{
	exit_status_controler(exit_status, OP_SET_CODE);
}

int	get_exit_status(void)
{
	return (exit_status_controler(0, OP_GET_CODE));
}

void	clear_exit_status(void)
{
	exit_status_controler(0, OP_CLEAR_CODE);
}

static int	exit_status_controler(int exit_status, int op)
{
	static int	exit_code = 0;

	if (op == OP_SET_CODE)
		exit_code = exit_status;
	else if (op == OP_CLEAR_CODE)
		exit_code = 0;
	return (exit_code);
}
