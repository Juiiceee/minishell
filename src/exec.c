/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:30:36 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/05 13:47:09 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsingcommand(t_exec *cmd, t_mini *mini)
{
	char	**envpath;
	int		i;
	int 	status;

	i = 0;
	status = 0;
	if (ft_strchr(cmd->cmd[0], '/') != NULL)
	{
		if (what_is_error(cmd, mini, &status))
			return (free_child(mini), exit(status), 0);
		else
			return(0);
	}
	envpath = ft_split(pathenv(mini, "PATH"), ':');
	while (envpath && envpath[i])
	{
		if (!utilsparsingcom(envpath, &i, cmd))
			return (0);
	}
	if (envpath)
		freetab(envpath);
	if (what_is_error(cmd, mini, &status))
		return (free_child(mini), exit(status), 0);
	return (1);
}

void	ft_parse_exec(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->lst;
	mini->exe = NULL;
	while (tmp)
	{
		exe_lstadd_back(&mini->exe, exe_lstnew(tmp));
		if (tmp->data_type == PIPE)
		{
			ft_free(tmp->global);
			if (tmp->next)
				tmp = tmp->next;
			else if (!tmp->next)
				break ;
		}
		else 
			break ;
	}
}

int	exec_node(t_exec *cmd, t_mini *mini)
{
	mini->pid[mini->exe_n] = fork();
	if (mini->pid[mini->exe_n] == -1)
		return (1);
	if (mini->pid[mini->exe_n] == 0)
	{
		if (cmd->is_fdin == 0 && mini->exe_n != 0)
			dup2(mini->pipe[2 * mini->exe_n - 2], 0);
		if (cmd->is_fdout == 0 && cmd->next != NULL)
			dup2(mini->pipe[2 * mini->exe_n + 1], 1);
		closepipe(mini);
		if (cmd->builtin == 1)
			exec_builtins(cmd, mini);
		else
			utilsexec_node(cmd, mini);
	}
	close(mini->pipe[2 * mini->exe_n + 1]);
	return (0);
}

void	wait_child(t_mini *mini)
{
	int	status;
	int	i;
	int	mini_status_temp;

	i = 0;
	mini_status_temp = mini->exitstatus;
	status = 0;
	signal(SIGINT, SIG_IGN);
	while (i < mini->exe_size)
	{
		if (mini->pid[i])
		{
			waitpid(mini->pid[i], &status, 0);
			mini->exitstatus = WEXITSTATUS(status);
		}
		else
			mini->exitstatus = mini_status_temp;
		i++;
	}
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

void	ft_exec(t_mini *mini)
{
	t_exec	*tmp_exe;

	tmp_exe = mini->exe;
	if (!tmp_exe)
		return ;
	mini->exe_n = 0;
	mini->exe_size = ft_exesize(tmp_exe);
	mini->pid = ft_calloc((sizeof (pid_t)), (mini->exe_size));
	init_pipe(mini);
	while (mini->exe_n < mini->exe_size && tmp_exe)
	{
		if (!utilsft_exec(mini, tmp_exe))
		{
			mini->exitstatus = 1;
			tmp_exe = tmp_exe->next;
			close(mini->pipe[2 * mini->exe_n + 1]);
			mini->exe_n++;
			continue ;
		}
		tmp_exe = tmp_exe->next;
	}
	return (closepipe(mini), wait_child(mini), ft_execlear(&mini->exe,
			*ft_free), free(mini->input), free(mini->pid),
				ft_tokclean(&mini->lst));
}
