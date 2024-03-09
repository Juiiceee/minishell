/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:32:33 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/09 14:25:08 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*pathenv(t_mini *mini, char *find)
{
	int		check;
	t_list	*st;

	st = mini->env;
	check = 1;
	if (!st || !st->content)
		return (NULL);
	while (check && st->next != NULL)
	{
		check = ft_strncmp(find, (char *)st->content, ft_strlen(find));
		if (check == 0)
			break ;
		st = st->next;
	}
	check = ft_strncmp(find, (char *)st->content, ft_strlen(find));
	if (check == 0)
		return ((char *)st->content + (ft_strlen(find) + 1));
	return (NULL);
}

int	recouser(t_mini *mini)
{
	mini->user = ft_strdup(pathenv(mini, "USER"));
	if (!mini->user)
	{
		mini->user = ft_strdup(pathenv(mini, "LOGNAME"));
		if (!mini->user)
			return (1);
	}
	return (0);
}
