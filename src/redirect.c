/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:18:05 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/09 16:43:33 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input(t_mini *mini, t_exec *exec)
{
	int	fd;

	if (exec->in)
	{
		if (ft_strlen(exec->in[0]) == 2)
		{
			fd = heredoc(exec->in[1], mini);
			if (fd < 0)
				return (mini->exitstatus = 1, 0);
			dup2(fd, 0);
			return (close(fd), 1);
		}
		else if (ft_strlen(exec->in[0]) == 1)
		{
			fd = open(exec->in[1], O_RDONLY);
			if (fd < 0)
				return (mini->exitstatus = 1, 0);
			dup2(fd, 0);
			return (close(fd), 1);
		}	
	}
	return (1);
}

int	output(t_mini *mini, t_exec *exec)
{
	int	fd;

	if (exec->out)
	{
		if (!ft_strncmp(exec->out[0], ">", 1))
		{
			fd = open(exec->out[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (mini->exitstatus = 1, 0);
			dup2(fd, 1);
			return (close(fd), 1);
		}
		else if (!ft_strncmp(exec->out[0], ">>", 2))
		{
			fd = open(exec->out[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (mini->exitstatus = 1, 0);
			dup2(fd, 1);
			return (close(fd), 1);
		}
	}
	return (1);
}
