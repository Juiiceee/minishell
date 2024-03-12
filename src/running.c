/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:53:08 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/12 12:23:49 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signalexit;

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

int	checkisdir(t_mini *mini)
{
	mini->dossier.st_mode = 0;
	if (!ft_strncmp(mini->exe->cmd[0], "./", 2) || !ft_strncmp(mini->exe->cmd[0], "/", 1))
	{
		lstat(mini->exe->cmd[0], &mini->dossier);
		if (S_ISDIR(mini->dossier.st_mode))
			return (ft_printerr("%s: Is a directory\n", mini->exe->cmd[0]),
				mini->exitstatus = 126, 1);
	}
	return (0);
}

int	insiderunning(t_mini *mini)
{
	recocp(mini);
	createprename(mini);
	mini->input = readline(mini->userstr);
	if (g_signalexit == 130)
	{
		mini->exitstatus = g_signalexit;
		g_signalexit = 0;
	}
	free(mini->userstr);
	free(mini->currentpath);
	if (!mini->input)
		return (1);
	mini->lst = ft_tokenizer(mini->input, mini);
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
	ft_parse_exec(mini);
	if (checkisdir(mini))
		return (0);
	ft_exec(mini);
	dup2(mini->clear_fd[0], 0);
	dup2(mini->clear_fd[1], 1);
	return (0);
}

void	running(t_mini *mini)
{
	while (1)
	{
		if (insiderunning(mini))
		{
			ft_envclean(&mini->env);
			printf("exit\n");
			break ;
		}
	}
}
