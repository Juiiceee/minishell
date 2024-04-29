/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:39:20 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/29 15:03:49 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_mini *mini, char *find)
{
	int		check;
	t_list	*st;

	st = mini->env;
	check = 1;
	if (!st || !st->content)
		return ;
	while (check && st->next)
	{
		check = ft_strncmp(find, (char *)st->content, ft_strlen(find));
		if (check == 0)
			break ;
		st = st->next;
	}
	check = ft_strncmp(find, (char *)st->content, ft_strlen(find));
	if (check == 0)
		free_list_element(&mini->env, st);
	return (free(find));
}
