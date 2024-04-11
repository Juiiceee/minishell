/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:26:35 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/11 12:29:02 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_exit_signal(t_mini *mini, int status)
{
	signal(SIGINT, recosigint);
	if (WIFEXITED(status))
		mini->exitstatus = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		mini->exitstatus = WTERMSIG(status);
		if (mini->exitstatus != 0x83)
			mini->exitstatus += 0b10000000;
		printf("\n");
	}
}
