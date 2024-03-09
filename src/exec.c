/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:30:36 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/09 12:36:45 by lbehr            ###   ########.fr       */
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
	mini->pid[mini->exe_n] = fork();
	if (mini->pid[mini->exe_n] == -1)
		return (1);
	if (mini->pid[mini->exe_n] == 0)
	{
		if (!cmd->in && mini->exe_n != 0)
			dup2(mini->pipe[2 * mini->exe_n - 2], 0);
		if (!cmd->out && cmd->next)
			dup2(mini->pipe[2 * mini->exe_n + 1], 1);
		closepipe(mini);
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
	close(mini->pipe[2 * mini->exe_n + 1]);
	return (0);
}

void wait_child(t_mini *mini)
{
	int		status;
	int 	i;

	i = 0;
	while (i < mini->exe_size)
	{
		if (mini->pid[i])
		{
			waitpid(mini->pid[i], &status, 0);
			mini->exitstatus = WEXITSTATUS(status);
		}
		i++;
	}
}

void	ft_exec(t_mini *mini)
{
	t_exec *tmp_exe;
	
	tmp_exe = mini->exe;
	if (!tmp_exe)
		return ;
	mini->exe_n = 0;
	mini->exe_size = ft_exesize(tmp_exe);
	mini->pid = ft_calloc((sizeof (pid_t)), (mini->exe_size));
	init_pipe(mini);
	while (mini->exe_n < mini->exe_size && tmp_exe)
	{
		if(!input(mini, tmp_exe))
		{
			tmp_exe = tmp_exe->next;
			close(mini->pipe[2 * mini->exe_n + 1]);
			mini->exe_n++;
			continue ;
		}
		output(mini, tmp_exe);
		if (tmp_exe->builtin == 1 && mini->exe->next == NULL)
			exec_builtins(tmp_exe, mini);
		else 
			exec_node(tmp_exe, mini);
		tmp_exe = tmp_exe->next;
		mini->exe_n++;
	}
	closepipe(mini);
	wait_child(mini);
	ft_execlear(&mini->exe, *ft_free);
	free(mini->tabcmd);
}
