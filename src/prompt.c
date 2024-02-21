/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:32:33 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/21 16:17:19 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*pathenv(char **env, char *find)
{
	int	check;
	int	lenght;

	check = 1;
	if (!env)
		return (NULL);
	lenght = ft_strlen(find);
	while (check && *env)
	{
		env++;
		check = ft_strncmp(find, *env, lenght);
	}
	if (check == 0)
		return (*env + (lenght + 1));
	return (NULL);
}

int	recouser(t_mini *mini)
{
	mini->user = ft_strdup(pathenv(mini->env, "USER"));
	if (!mini->user)
	{
		mini->user = ft_strdup(pathenv(mini->env, "LOGNAME"));
		if (!mini->user)
			return (1);
	}
	return (0);
}
