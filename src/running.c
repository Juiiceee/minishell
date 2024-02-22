/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:53:08 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/22 14:23:00 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	createprename(t_mini *mini)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(getenv("USER"), "@minishell:");
	tmp2 = ft_strjoin(tmp, mini->currentpath);
	free(tmp);
	mini->userstr = ft_strjoin(tmp2, "$ ");
	free(tmp2);
}

int	insiderunning(t_mini *mini)
{
	recocp(mini);
	createprename(mini);
	mini->input = readline(mini->userstr);
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
	free(mini->userstr);
	free(mini->currentpath);
	if (!ft_strncmp(mini->input, "cd", 2))
		chdir("../");
	else if (!ft_strncmp(mini->input, "exit", 4))
	{
		printf("exit\n");
		return 1;
	}
	return (0);
}

void	running(t_mini *mini)
{
	int	running;

	running = 1;
	while (running)
	{
		if (insiderunning(mini))
			break;
	}
}
