/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilstab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:49 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/28 15:32:58 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	tablength(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	**lsttotab(t_mini *mini)
{
	int	i;
	char	**tab;
	t_list	*st;
	t_list	*lst;

	st = mini->env;
	lst = mini->env;
	i = 0;
	tab = malloc((sizeof(char *) * (ft_lstsize(lst) + 1)));
	if (!tab)
		return (NULL);
	while (st)
	{
		tab[i] = ft_strdup((char *)st->content);
		i++;
		st = st->next;
	}
	tab[i] = NULL;
	return (tab);
}
