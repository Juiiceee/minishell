/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:10:02 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/12 19:36:17 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	what_is_error(t_exec *cmd, t_mini *mini)
{
	if ((cmd->cmd[0][0] == '/' || cmd->cmd[0][0] == '.') && access(cmd->cmd[0], F_OK))
	{
		ft_printerr("%s: no such file or directory\n", cmd->cmd[0]);
		return(127);
	}
	else if ((cmd->cmd[0][0] == '/' || cmd->cmd[0][0] == '.') && checkisdir(mini))
	{
		ft_printerr("%s: Is a directory\n", cmd->cmd[0]);
		return(126);
	}
	else if ((cmd->cmd[0][0] == '/' || cmd->cmd[0][0] == '.') && access(cmd->cmd[0], X_OK))
	{
		ft_printerr("%s: permission denied\n", cmd->cmd[0]);
		return(126);
	}
	// else
	// {
	// 	ft_printerr("%s: command not found\n", cmd->cmd[0]);
	// 	return(127);
	// }
	return (0);
}

void free_child(t_mini *mini)
{
	ft_free(mini->tabenv);
	free(mini->user);
	free(mini->pid);
	free(mini->input);
	rl_clear_history();
	ft_execlear(&mini->exe, *ft_free);
	ft_lstclear(&mini->env, *free);
	free(mini->tabcmd); 
}

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
	int	status;

	status = 0;
	status = what_is_error(cmd, mini);
	if (!parsingcommand(cmd, mini))
		execve(cmd->cmd[0], cmd->cmd, mini->tabenv);
	ft_printerr("%s: command not found\n", cmd->cmd[0]);
	free_child(mini);
	exit (status);
}

int	utilsft_exec(t_mini *mini, t_exec *tmp_exe)
{
	if (!input(mini, tmp_exe))
		return (0);
	if (!output(mini, tmp_exe))
		return (0);
	if (mini->exe->builtin == 1 && mini->exe->next == NULL)
		exec_builtins(tmp_exe, mini);
	else
		exec_node(tmp_exe, mini);
	if (tmp_exe->is_fdout == 1)
		dup2(mini->clear_fd[1], 1);
	mini->exe_n++;
	return (1);
}
