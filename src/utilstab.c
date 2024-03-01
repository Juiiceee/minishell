/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilstab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:49 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/01 10:56:17 by lbehr            ###   ########.fr       */
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

void	lsttotab(t_mini *mini)
{
	int	i;
	t_list	*st;
	t_list	*lst;

	st = mini->env;
	lst = mini->env;
	i = 0;
	mini->tabenv = malloc((sizeof(char *) * (ft_lstsize(lst) + 1)));
	if (!mini->tabenv)
		return ;
	while (st)
	{
		mini->tabenv[i] = ft_strdup((char *)st->content);
		i++;
		st = st->next;
	}
	mini->tabenv[i] = NULL;
}

void	refreshtab(t_mini *mini)
{
	if (mini->tabenv)
		freetab(mini->tabenv);
	lsttotab(mini);
	if (!mini->tabenv)
		return ;
}
