/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:53:08 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/02 15:43:07 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	exitstatus;

void	createprename(t_mini *mini)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(pathenv(mini, "USER"), "@minishell:");
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
	free(mini->userstr);
	free(mini->currentpath);
	if (!mini->input)
		return (1);
	mini->lst = ft_tokenizer(mini->input, mini);
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
	ft_parse_exec(mini);
	ft_exec(mini);
	dup2(mini->clear_fd, 0);
	// closepipe(mini);
	return (0);
}

void	running(t_mini *mini)
{
	int	running;

	running = 1;
	while (running)
	{
		if (insiderunning(mini))
		{
			printf("exit\n");
			break;
		}
	}
}
