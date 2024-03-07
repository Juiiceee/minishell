/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:30:36 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/07 16:17:42 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsingcommand(t_exec *cmd, t_mini *mini)
{
	char	*tmp;
	char	*tmp1;
	char	**envpath;
	int		i;

	i = 0;
	if (ft_strchr(cmd->cmd[0], '/') != NULL)
		return (0);
	envpath = ft_split(pathenv(mini, "PATH"), ':');
	if (!envpath)
		return (1);
	while (envpath[i])
	{
		tmp = ft_strjoin(envpath[i], "/");
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
		i++;
	}
	freetab(envpath);
	return(1);
}

void	ft_parse_exec(t_mini *mini)
{
	t_token *tmp;

	tmp = mini->lst;
	mini->exe = NULL;
	while (tmp)
	{
		exe_lstadd_back(&mini->exe, exe_lstnew(tmp));
		while (tmp->data_type != PIPE && tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->data_type == PIPE && tmp->next)
		{
			ft_free(tmp->global);
			tmp = tmp->next;
		}
		else 
			break ;
	}
	ft_tokclean(&mini->lst);
}

int	exec_node(t_exec *cmd, t_mini *mini)
{
	int		status;

	if (pipe(mini->pipe) == -1)
		return (1);
	mini->pid = fork();
	if (mini->pid == -1)
		return (1);
	if (mini->pid == 0)
	{
		close(mini->pipe[0]);
		if (!cmd->out)
			dup2(mini->pipe[1], 1);
		if (cmd->builtin == 1)
			exec_builtins(cmd, mini);
		else
		{
			if (!parsingcommand(cmd, mini))
				execve(cmd->cmd[0], cmd->cmd, mini->tabenv);
			ft_printerr("%s: command not found\n", cmd->cmd[0]);
			ft_free(mini->tabenv);
			free(mini->user);
			ft_execlear(&mini->exe, *ft_free);
			ft_lstclear(&mini->env, *free);
			free(mini->tabcmd);
			exit (127);
		}
	}
	waitpid(-1, &status, 0);
	mini->exitstatus = WEXITSTATUS(status);
	close(mini->pipe[1]);
	dup2(mini->pipe[0], 0);
	return (0);
}

int	last_node(t_exec *cmd, t_mini *mini)
{
	int		status;

	mini->pid = fork();
	if (mini->pid == -1)
		return (1);
	if (mini->pid == 0)
	{
		if (cmd->builtin == 1)
			exec_builtins(cmd, mini);
		if (!parsingcommand(cmd, mini))
			execve(cmd->cmd[0], cmd->cmd, mini->tabenv);
		ft_printerr("%s: command not found\n", cmd->cmd[0]);
		ft_free(mini->tabenv);
		free(mini->user);
		ft_execlear(&mini->exe, *ft_free);
		ft_lstclear(&mini->env, *free);
		free(mini->tabcmd);
		exit (127);
	}
	waitpid(-1, &status, 0);
	mini->exitstatus = WEXITSTATUS(status);
	return (0);
}

void	ft_exec_one(t_exec *cmd, t_mini *mini)
{
	if (!input(mini, cmd))
		return((void) ft_printerr(" No such file or directory\n"));
	if (!output(mini, cmd))
		return((void) ft_printerr(" No such file or directory\n"));
	if (cmd->builtin == 1 && mini->exe->next == NULL)
		exec_builtins(cmd, mini);
	else 
		last_node(cmd, mini);
}

void	ft_exec(t_mini *mini)
{
	t_exec *tmp_exe;
	
	tmp_exe = mini->exe;
	if (!tmp_exe)
		return ;
	while (tmp_exe->next != NULL)
	{
		input(mini, tmp_exe);
		output(mini, tmp_exe);
		exec_node(tmp_exe, mini);
		tmp_exe = tmp_exe->next;
	}
	ft_exec_one(tmp_exe, mini);
	ft_execlear(&mini->exe, *ft_free);
	free(mini->tabcmd);
	waitpid(-1, NULL, 0);
}
