/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:18:05 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/05 15:26:56 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	input(t_mini *mini, t_exec *exec)
{
	int fd;
	if (exec->in)
	{
		if (ft_strlen(exec->in[0]) == 2)
		{
			fd = heredoc(exec->in[1]);
			if (!fd)
				mini->exitstatus = 1;
			else 
			{
				dup2(fd, 0);
				close(fd);
			}
		}
		else if (ft_strlen(exec->in[0]) == 1)
		{
			fd = open(exec->in[1], O_RDONLY);
			if (!fd)
				mini->exitstatus = 1;
			else 
			{
				dup2(fd, 0);
				close(fd);
			}
		}	
	}
}

void	output(t_mini *mini, t_exec *exec)
{
	int fd;
	
	if (exec->out)
	{
		if (!ft_strncmp(exec->out[0], ">", 1))
		{
			fd = open(exec->out[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!fd)
				mini->exitstatus = 1;
			else
				dup2(fd, 1);
		}
		else if (!ft_strncmp(exec->out[0], ">>", 2))
		{
			fd = open(exec->out[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (!fd)
				mini->exitstatus = 1;
			dup2(fd, 1);
		}
		else
		{
			ft_free(exec->out);
			exec->out = NULL;
		}
	}
}
