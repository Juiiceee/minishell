/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:07:36 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/28 10:19:49 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	recosigint(int sig)
{
	(void)sig;
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
