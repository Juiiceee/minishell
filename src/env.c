/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:33 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/28 14:12:36 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	recoenv(t_mini *mini, char **argv)
{
	int	i;

	mini->env = NULL;
	i = 0;
	if (!argv)
		return (1);
	while (argv[i])
		ft_lstadd_back(&mini->env, ft_lstnew((char *)argv[i++]));
	return (0);
}

int	recocp(t_mini *mini)
{
	mini->currentpath = getcwd(NULL, 1024);
	if (!mini->currentpath)
		return (1);
	return (0);
}
