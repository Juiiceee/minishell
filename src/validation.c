/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:42:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/10 11:53:30 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_inpt_error(t_mini *mini)
{
	free(mini->input);
	ft_tokclear_str(&mini->lst);
}

int	input_validation(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->lst;
	if (!tmp || !ft_strlen(mini->lst->global[0]))
		return (1);
	if (mini->lst->data_type == PIPE)
		return (1);
	while (tmp != NULL)
	{
		if (tmp->data_type == DONT_EXIST)
			return (1);
		else if ((tmp->data_type == PIPE) && (!tmp->next
				|| tmp->next->data_type == PIPE))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
