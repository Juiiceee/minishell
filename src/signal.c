/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:07:36 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/02 12:48:43 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exitstatus;

static void	recosigint(int sig)
{
	(void)sig;
	exitstatus = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

static void	recosigquit(int sig)
{
	(void)sig;
	rl_replace_line("  ", 2);
	rl_on_new_line();
	rl_redisplay();
}

void	recosignal(void)
{
	signal(SIGINT, recosigint);
	signal(SIGQUIT, recosigquit);
}
