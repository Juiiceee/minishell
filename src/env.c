/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:33 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/21 17:42:25 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	recoenv(t_mini *mini, char **argv)
{
	int	length;
	int	i;

	length = tablength(argv);
	i = 0;
	if (!length)
		return (1);
	mini->env = ft_calloc(sizeof(char *), length + 1);
	if (!mini->env)
		return (1);
	while (argv[i])
	{
		mini->env[i] = ft_strdup(argv[i]);
		if (!mini->env[i])
			return (1);
		i++;
	}
	mini->env[i] = NULL;
	return (0);
}

int	recocp(t_mini *mini)
{
	mini->currentpath = getcwd(NULL, 1024);
	if (!mini->currentpath)
		return (1);
	return (0);
}