/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:10:02 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/12 10:51:33 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utilsparsingcom(char **envpath, int *i, t_exec *cmd)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(envpath[*i], "/");
	tmp1 = ft_strjoin(tmp, cmd->cmd[0]);
	free(tmp);
	if (!access(tmp1, X_OK))
	{
		free(cmd->cmd[0]);
		cmd->cmd[0] = ft_strdup(tmp1);
		freetab(envpath);
		free(tmp1);
		return (0);
	}
	free(tmp1);
	(*i)++;
	return (1);
}

void	utilsexec_node(t_exec *cmd, t_mini *mini)
{
	if (!parsingcommand(cmd, mini))
		execve(cmd->cmd[0], cmd->cmd, mini->tabenv);
	ft_printerr("%s: command not found\n", cmd->cmd[0]);
	ft_free(mini->tabenv);
	free(mini->user);
	free(mini->pid);
	free(mini->input);
	ft_execlear(&mini->exe, *ft_free);
	ft_lstclear(&mini->env, *free);
	free(mini->tabcmd);
	exit (127);
}

int		utilsft_exec(t_mini *mini, t_exec *tmp_exe)
{
	if (!input(mini, tmp_exe))
		return (0);
	if (!output(mini, tmp_exe))
		return (0);
	if (mini->exe->builtin == 1 && mini->exe->next == NULL)
		exec_builtins(tmp_exe, mini);
	else
		exec_node(tmp_exe, mini);
	mini->exe_n++;
	return (1);
}
