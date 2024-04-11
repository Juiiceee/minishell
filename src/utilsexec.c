/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:10:02 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/11 11:56:19 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	what_is_error(t_exec *cmd, t_mini *mini, int *status)
{
	if ((cmd->cmd[0][0] == '/'
		|| cmd->cmd[0][0] == '.') && access(cmd->cmd[0], F_OK))
	{
		printflu(9, cmd->cmd[0]);
		return (*status = 127, 1);
	}
	else if ((cmd->cmd[0][0] == '/'
		|| cmd->cmd[0][0] == '.') && checkisdir(mini))
	{
		printexe(8, cmd->cmd[0]);
		return (*status = 126, 1);
	}
	else if ((cmd->cmd[0][0] == '/'
		|| cmd->cmd[0][0] == '.') && (access(cmd->cmd[0], X_OK) < 0))
	{
		printflu(10, cmd->cmd[0]);
		return (*status = 126, 1);
	}
	return (0);
}

void	free_child(t_mini *mini)
{
	ft_tokclean(&mini->lst);
	ft_free(mini->tabenv);
	free(mini->user);
	free(mini->pid);
	free(mini->input);
	rl_clear_history();
	ft_execlear(&mini->exe, *ft_free);
	ft_lstclear(&mini->env, *free);
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
	signal(SIGQUIT, SIG_DFL);
	if (!parsingcommand(cmd, mini))
		execve(cmd->cmd[0], cmd->cmd, mini->tabenv);
	printflu(11, cmd->cmd[0]);
	free_child(mini);
	exit (127);
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
