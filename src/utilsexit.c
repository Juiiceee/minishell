/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:59:01 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/11 13:01:35 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utilsexit(t_mini *mini, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1][0] == '+' || cmd[1][0] == '-')
		i++;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			if (mini->exe_size != 1)
			{
				printexe(2, cmd[1]);
				child_clean_exit(mini, 2);
			}
			return (printexe(2, cmd[1]), clean_for_exit(mini, 2));
		}
		i++;
	}
	if (mini->exe_size != 1)
		child_clean_exit(mini, ft_atoi(cmd[1]));
	clean_for_exit(mini, ft_atoi(cmd[1]));
}
