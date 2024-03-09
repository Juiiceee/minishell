/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:19:46 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/09 14:20:06 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exportvalueseul(t_mini *mini, char *find)
{
	t_list	*st;

	st = mini->env;
	if (!st || !st->content)
		return ;
	if (!pathenv(mini, find))
		ft_lstadd_back(&mini->env, ft_lstnew(find));
	return ;
}
