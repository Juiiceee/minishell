/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:30:36 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/28 11:49:06 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	isslach(char *cmd)
{
	if (!cmd)
		return (1);
	while (cmd)
	{
		if (cmd == '/')
			return (0);
		cmd++;
	}
	return (1);
}

int	parsingcommand(t_exec *cmd, t_mini *mini)
{
	char	*tmp;
	char	*tmp1;
	char	**envpath;
	int		i;

	i = 0;
	envpath = ft_split(pathenv(mini->env, "PATH"), ':');
	if (!envpath)
		return (1);
	if (access(cmd->cmd[0], X_OK))
	{
		if (!ft_strchr(cmd, '/'))
		{
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
		}
		return (1);
	}
	return (0);
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
		if (parsingcommand(cmd, mini))
			return (printf("Command not found <3\n"), 0);
		execve(cmd->cmd[0], cmd->cmd, mini->env);
	}
	else
	{
		waitpid(-1, NULL, 0);
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
		{
			cmd->in_fd = open(cmd->in[1], O_RDONLY, 0644);
			dup2(cmd->in_fd, 0);
		}
		if (cmd->out)
		{
			cmd->out_fd = open(cmd->out[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(cmd->out_fd, 1);
		}
		execve(ft_strjoin("/usr/bin/", cmd->cmd[0]), cmd->cmd, mini->env);
	}
	waitpid(-1, NULL, 0);
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
	waitpid(-1, NULL, 0);
}
