/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:53:40 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/09 01:34:06 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_pipe(t_mini *mini)
{
	int i;

	i = 0;
	mini->pipe_n = 0;
	mini->pipe = ft_calloc((sizeof (int)), (mini->exe_size * 2));
	if (!mini->pipe)
		return ;
	while (i < mini->exe_size)
	{
		if (pipe(mini->pipe + i * 2) < 0)
			return ;
		i++;
	}
}

void	closepipe(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->exe_size * 2)
		close(mini->pipe[i++]);
}
