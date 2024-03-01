/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:39:20 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/01 15:17:52 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset(char **cmd, t_mini *mini)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 1;
	while (cmd[j])
	{
		while (cmd[j][i] != '=' && cmd[j][i])
			i++;
		unset(mini, ft_substr(cmd[j], 0, i));
		i = 0;
		j++;
	}
	refreshtab(mini);
}
