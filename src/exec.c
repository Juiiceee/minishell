/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:30:36 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/27 16:10:55 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*int	parsingcommand(t_pipex *pipex, char **argv, int nb)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strlen(argv[nb]) == 0)
		return (0);
	pipex->argcmd = ft_split(argv[nb], ' ');
	if (access(pipex->argcmd[0], X_OK))
	{ 
		if (!pipex->envpath)
			return (0);
		while (pipex->envpath[i])
		{
			tmp = ft_strjoin(pipex->envpath[i], "/");
			pipex->cmd = ft_strjoin(tmp, pipex->argcmd[0]);
			free(tmp);
			if (!access(pipex->cmd, X_OK))
				return (1);
			free(pipex->cmd);
			i++;
		}
		return (0);
	}
	pipex->cmd = ft_strdup(pipex->argcmd[0]);
	return (1);
}*/

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
			tmp = tmp->next;
		else 
			break ;
	}
	// mini->pipe = malloc(sizeof(int) * (mini->pipe_nb * 2));
}

void exec_node(t_exec *cmd, t_mini *mini)
{
	pid_t	pid;

	if (pipe(mini->pipe) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (cmd->in)
		{
			cmd->in_fd = open(cmd->in[1], O_RDONLY, 0644);
			dup2(cmd->in_fd, 0);
		}
		if (cmd->out)
		{
			cmd->out_fd = open(cmd->out[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(cmd->out_fd, 1);
		}
		else
			dup2(mini->pipe[1], 1);
		close(mini->pipe[0]);
		execve(ft_strjoin("/usr/bin/", cmd->cmd[0]), cmd->cmd, mini->env);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(mini->pipe[1]);
		dup2(mini->pipe[0], 0);
	}
}

void last_node(t_exec *cmd, t_mini *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (cmd->in)
			cmd->in_fd = open(cmd->in[1], O_RDONLY, 0644);
		if (cmd->out)
			cmd->out_fd = open(cmd->out[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		execve(ft_strjoin("/usr/bin/", cmd->cmd[0]), cmd->cmd, mini->env);
	}
	waitpid(pid, NULL, 0);
	return ;
}

void	ft_exec(t_mini *mini)
{
	if (!mini->exe)
		return ;
	while (mini->exe->next != NULL)
	{
		exec_node(mini->exe, mini);
		mini->exe = mini->exe->next;
	}
	last_node(mini->exe, mini);
	mini->exe = NULL;
}
