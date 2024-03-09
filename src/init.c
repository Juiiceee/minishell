/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:33:07 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/09 13:15:47 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	envmin(t_mini *mini)
{
	if (!pathenv(mini,"PWD"))
		export(mini, "PWD", getcwd(NULL, 0));
	if (!pathenv(mini,"SHLVL"))
		export(mini, "SHLVL", "1");
	if (!pathenv(mini,"_"))
		export(mini, "_", "/usr/bin/env");
}

int	init(t_mini *mini, char **env)
{
	if (recoenv(mini, env))
		return (1);
	if (recouser(mini))
		return (1);
	envmin(mini);
	lsttotab(mini);
	mini->exitstatus = 0;
	mini->clear_fd[0] = dup(0);
	mini->clear_fd[1] = dup(1);
	mini->tabcmd = NULL;
	return (0);
}
