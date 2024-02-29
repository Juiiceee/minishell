/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:33:07 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/29 13:05:07 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init(t_mini *mini, char **env)
{
	if (recoenv(mini, env))
		return (1);
	if (recouser(mini))
		return (1);
	lsttotab(mini);
	mini->clear_fd = dup(0);
	return (0);
}
