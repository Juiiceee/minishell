/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:18:05 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/12 09:46:38 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input(t_mini *mini, t_exec *exec)
{
	int	fd;

	if (exec->is_fdin == 1)
	{
		dup2(exec->fdin, 0);
		return (close(exec->fdin), 1);
	}
	else if (exec->is_fdin == 2)
		return (0);
	else if (exec->is_fdin == 3)
	{
		fd = heredoc(exec->in[1], mini);
		if (fd < 0)
			return (mini->exitstatus = 1, 0);
		dup2(fd, 0);
		return (close(fd), 1);
	}
	return (1);
}

int	output(t_mini *mini, t_exec *exec)
{
	(void) mini;
	
	if (exec->is_fdout == 1)
	{
		dup2(exec->fdout, 1);
		return (close(exec->fdout), 1);
	}
	else if (exec->is_fdout == 2)
		return (0);
	return (1);
}

void parse_redirect_in(t_token *tmp, t_exec *newlst)
{
	int fd;
	
	newlst->in = tmp->global;
	if (ft_strlen(tmp->global[0]) == 2)
		newlst->is_fdin = 3;
	else if (ft_strlen(tmp->global[0]) == 1 && newlst->is_fdin != 2
			&& newlst->is_fdout != 2)
	{
		fd = open(tmp->global[1], O_RDONLY);
		if (fd < 0)
		{
			if (newlst->fdin)
				close(newlst->fdin);
			newlst->is_fdin = 2;
			return ;
		}
		else 
		{
			newlst->is_fdin = 1;
			if (newlst->fdin)
				close(newlst->fdin);
			newlst->fdin = fd;
		}
	}
}

void parse_redirect_out(t_token *tmp, t_exec *newlst)
{
	int fd;

	newlst->out = tmp->global;
	if (ft_strlen(tmp->global[0]) == 1 && newlst->is_fdout != 2 
		&& newlst->is_fdin != 2)
		fd = open(tmp->global[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strlen(tmp->global[0]) == 2 && newlst->is_fdout != 2 
		&& newlst->is_fdin != 2)
		fd = open(tmp->global[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return ;
	if (fd < 0)
	{
		newlst->is_fdout = 2;
		if (newlst->fdout)
			close(newlst->fdout);
		return ;
	}
	else 
	{
		newlst->is_fdout = 1;
		if (newlst->fdout)
			close(newlst->fdout);
		newlst->fdout = fd;
	}
}
