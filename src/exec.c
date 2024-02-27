/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:30:36 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/27 11:54:34 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_exec(t_mini *mini)
{
	t_token *tmp;
	t_exec	*exe;
	t_exec	*old;
	int pipe;
	int fd[2];

	mini->pid = fork();
	if (mini->pid == 0)
	{
		tmp = mini->lst;
		exe = NULL;
		pipe = 0;
		while (tmp)
		{
			old = malloc(sizeof (*exe));
			old->in = NULL;
			old->out = NULL;
			while (tmp && tmp->data_type != PIPE)
			{
				if (tmp->data_type == CMD)
					old->cmd = tmp->global;
				if (tmp->data_type == IN_REDIRECT)
					old->in = tmp->global;
				if (tmp->data_type == OU_REDIRECT)
					old->out = tmp->global;
				if (!tmp->next)
					break ;
				tmp = tmp->next;
			}
			if (tmp->data_type == PIPE)
			{
				pipe++;
				tmp = tmp->next;
			}
			else
				tmp = tmp->next;
			if (exe)
				exe->next = old;
			else
				exe = old;
		}
		/*if (exe->in)
		{
			fd[0] = open(exe->in[1], O_RDONLY, 0777);
			dup2(fd[0], 0);
		}
		if (exe->out)
		{
			fd[1] = open(exe->out[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(fd[1], 1);
		}
		else
		{
			fd[1] = open("/dev/stdout", O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(fd[1], 1);
		}*/
		execve(ft_strjoin("/usr/bin/", exe->cmd[0]), exe->cmd, mini->env);
	}
}
