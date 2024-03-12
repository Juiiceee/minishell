/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:07:36 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/12 10:51:33 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signalexit;

static void	recosigint(int sig)
{
	(void)sig;
	g_signalexit = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

void	recosignal(void)
{
	signal(SIGINT, recosigint);
	signal(SIGQUIT, SIG_IGN);
}
