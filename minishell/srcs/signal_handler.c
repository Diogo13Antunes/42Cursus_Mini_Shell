/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:31:32 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/13 15:20:46 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void config_signal(void (*f)())
{
    struct sigaction sa;

    sigemptyset(&(sa.sa_mask));
    sa.sa_flags = 0;
    sa.sa_handler = f;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        printf("signation error\n");
}
